#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <complex.h>
#include <time.h>
#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/mat_ZZ.h>
#include <gmp.h>
#include "blake2.h"
#include "blake2-kat.h"

#include "Sampling.h"
#include "params.h"
#include "FFT.h"
#include "Random.h"
#include "Algebra.h"
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
using namespace std;
using namespace NTL;

const ZZX phi = Cyclo();


//==============================================================================
//Generates from parameters N and q :
// - a public key : polynomial h
// - a private key : polynomials f,g,F,G
//==============================================================================
void Keygen(ZZ_pX& PublicKey, ZZX* PrivateKey)
{
    ZZ SqNorm;
    ZZX f,g,F,G;

    SqNorm = conv<ZZ>(1.36*q0/2);

    GenerateBasis(f, g, F, G, SqNorm);
	
	//added by me ============
	
	
	
	//added by me ==============
	
    PrivateKey[0] = f;
    PrivateKey[1] = g;
    PrivateKey[2] = F;
    PrivateKey[3] = G;

    for(unsigned int i=0; i<4; i++)
    {
            PrivateKey[i].SetLength(N0);
    }

    PublicKey = Quotient(f, g);
}



void myKeygen(ZZ_pX& PublicKey, ZZX* PrivateKey)
{
    ZZ SqNorm;
    ZZX f,g,F,G;

    SqNorm = conv<ZZ>(1.36*q0/2);

    GenerateBasis(f, g, F, G, SqNorm);
	
	//added by me ============
	
	
	
	//added by me ==============
	
    PrivateKey[0] = f;
    PrivateKey[1] = g;
    PrivateKey[2] = F;
    PrivateKey[3] = G;

    for(unsigned int i=0; i<4; i++)
    {
            PrivateKey[i].SetLength(N0);
    }

    PublicKey = Quotient(f, g);
}




//==============================================================================
//Computes the private basis B from private key PrivateKey and parameter N
//==============================================================================
void CompletePrivateKey(mat_ZZ& B, const ZZX * const PrivateKey)
{
    ZZX f,g,F,G;
    f = PrivateKey[0];
    g = PrivateKey[1];
    F = PrivateKey[2];
    G = PrivateKey[3];

    f = -f;
    F = -F;

    B = BasisFromPolynomials(g, f, G, F);
}





void GPV(RR_t * v, const RR_t * const c, const RR_t s, const MSK_Data * const MSKD)
{

    int i;
    unsigned j;
    RR_t ci[2*N0], zi, cip, sip, aux;

    for(j=0; j<2*N0;j++)
    {
        ci[j] = c[j];
    }

//    for(j=0; j<2*N0; j++)
//    {
//
//    }    

    for(i=2*N0-1; i>=0; i--)
    {
        aux = (MSKD->GS_Norms)[i];
        cip = DotProduct(ci, MSKD->Bstar[i])/(aux*aux);
        sip = s/aux;
        zi = Sample4(cip, sip*PiPrime);

        for(j=0; j<2*N0; j++)
        {
            ci[j] -= zi*(MSKD->B)[i][j];
        }
    }

    for(j=0; j<2*N0; j++)
    {
        v[j] = c[j] - ci[j];
    }

}



//==============================================================================
//==============================================================================
//                            KeyGen
//==============================================================================
//==============================================================================


void CompleteMSK(MSK_Data * MSKD, ZZX * MSK)
{
    unsigned int i, j;
    mat_ZZ B0;

    for(i=0; i<4; i++)
    {
        MSKD->PrK[i] = MSK[i];
        ZZXToFFT(MSKD->PrK_fft[i], MSK[i]);
    }

    CompletePrivateKey(B0, MSK);

    for(i=0; i<2*N0; i++)
    {
        for(j=0; j<2*N0; j++)
        {
            MSKD->B[i][j] = ( (RR_t) conv<double>(B0[i][j]) );
        }
    }

    for(i=0; i<1; i++)
    {
        FastMGS(MSKD->Bstar, MSKD->B);
    }

    for(i=0; i<2*N0; i++)
    {
        MSKD->GS_Norms[i] = sqrt( DotProduct(MSKD->Bstar[i], MSKD->Bstar[i]) );
    }

    MSKD->sigma = 2*MSKD->GS_Norms[0];

}



void CompleteMPK(MPK_Data * MPKD, ZZ_pX MPK)
{
    MPKD->h = MPK;
    ZZXToFFT(MPKD->h_FFT, conv<ZZX>(MPK));
}


//==============================================================================
//==============================================================================
//                            Trapdoor
//==============================================================================
//==============================================================================


void PEKS_Trapdoor(ZZX SK_id[2], vec_ZZ id, const MSK_Data * const MSKD)
{
    unsigned int i;
    RR_t c[2*N0], sk[2*N0], sigma;
    ZZX f,g,aux;

/*	id[0] = q0-1;
	id[1] = q0-3;
	id[2] = q0-5;
	id[3] = q0-5;
	id[4] = q0-8;
	id[5] = q0/2;
	id[6] = q0-10;
	id[7] = q0-11;*/
//id = RandomVector();


    f = MSKD -> PrK[0];
    g = MSKD -> PrK[1];
    sigma = MSKD->sigma;
    SK_id[0].SetLength(N0);
    SK_id[1].SetLength(N0);

    for(i=0;i<N0;i++)
    {
        c[i] = ((RR_t) conv<double>(id[i])) ;
        c[i+N0] = 0;
    }
/*		cout<< "ID in trapdoor: ";
	for (int j = 0;j<N0;j++)
		cout << id[j]<< "   ";*/
	cout << endl;

    GPV(sk, c, sigma, MSKD);

    for(i=0; i<N0; i++)
    {
        sk[i] = c[i] - sk[i];
        sk[i+N0] = - sk[i+N0];
    }

    for(i=0; i<N0; i++)
    {
        SK_id[0][i] = sk[i];
        SK_id[1][i] = sk[i+N0];
    }


}

//==============================================================================
//==============================================================================
//                          Verify  Trapdoor
//==============================================================================
//==============================================================================



unsigned long  PEKS_Verify_Trapdoor( const ZZX SK_td[2], const vec_ZZ kw, const MSK_Data * const MSKD)
{
    unsigned int i;
    ZZX f,g,t,aux;

    f = MSKD -> PrK[0];
    g = MSKD -> PrK[1];
    
    t = conv<ZZX>(kw);
    aux = ((SK_td[0] - t)*f + g*SK_td[1])%phi;

    for(i=0; i<N0; i++)
    {
        aux[i] %= q1;
    }

    if( IsZero(aux) != 0)
    {
        cout << "The signature (s1,s2) doesn't verify the required equality [ (s1 - t)*f + g*s2 = 0 ] !\nActually, (s1 - t)*f + g*s2 = " << aux << endl << endl;
    }
    return IsZero(aux);
}

//==============================================================================
//==============================================================================
//                          PEKS
//==============================================================================
//==============================================================================




void PEKS_Enc(long C[2][N0],  long C2[N0],  long id0[N0], const MPK_Data * const MPKD)
{

    unsigned long i;
//	srand(3);

/*cout << "The ID in PEKS_ENC  :   ";
		for (int i = 0; i<N0 ; i++){
			
			cout << id0[i]<<"  ";
			}*/

/*	unsigned char z[32] = {0x54, 0xa2, 0xf8, 0x03, 0x1d, 0x18, 0xac, 0x77, 0xd2, 0x53, 0x92, 0xf2, 0x80, 0xb4, 0xb1, 0x2f, 0xac, 0xf1, 0x29, 0x3f, 0x3a, 0xe6, 0x77, 0x7d, 0x74, 0x15, 0x67, 0x91, 0x99, 0x53, 0x69, 0xc5};
	uint8_t hashed[64];
	long hashed2[64];
	uint8_t hash[2] = {0};
	blake2b(hashed, hash, z, 64, 2, 32);
	cout << "the hashed values are as follows";
	for (int i = 0; i<64 ; i++){
		hashed2[i]= hashed[i];
	 hashed2[i] << 17;}
	for (int i = 0; i<64 ; i++)
		cout << hashed2[i] << "  ";
		*/
/*	id0[0] =  100;
	id0[1] = 234;
	id0[2] = 12;
	id0[3] = 546;
	id0[4] = 98;
	id0[5] = 0;
	id0[6] = 0;
	id0[7] = q0-0;
	id0[8] =  q0 + 100023 - 6619531;
	id0[9] = 0;
	id0[10] = 0;
	id0[11] = 0;
	id0[12] = 0;
	id0[13] = 0;
	id0[14] = 500;
	id0[15] = 0;*/
	

    long r[N0], e1[N0], e2[N0];
    CC_t r_FFT[N0], t_FFT[N0], aux1_FFT[N0], aux2_FFT[N0];
	for(i=0; i<N0; i++)
        {
            C2[i] = (rand()%2);
        }
    for(i=0; i<N0; i++)
    {
        e1[i] = (rand()%3) - 1;
        e2[i] = (rand()%3) - 1;
        r[i] = (rand()%3) - 1;
    }
	
	//============================

		//----------------
    MyIntFFT(r_FFT, r);
    MyIntFFT(t_FFT, id0);




    for(i=0; i<N0; i++)
    {
        aux1_FFT[i] = r_FFT[i]*((MPKD->h_FFT)[i]);
        aux2_FFT[i] = r_FFT[i]*t_FFT[i];
    }

    MyIntReverseFFT(C[0], aux1_FFT);
    MyIntReverseFFT(C[1], aux2_FFT);

    for(i=0; i<N0; i++)
    {
        C[0][i] = (C[0][i] + e1[i]               + q0/2)%q0 - (q0/2);
        C[1][i] = (C[1][i] + e2[i] + (q0/2)*C2[i] + q0/2)%q0 - (q0/2);
    } 

}

//==============================================================================
//==============================================================================
//                          TEST
//==============================================================================
//==============================================================================



void PEKS_Test(long message[N0],  long C[2][N0], const CC_t * const SKid_FFT)
{
    unsigned int i;
    CC_t c0_FFT[N0], aux_FFT[N0];
	/*        for(int j=0; j<N0; j++)
        {
            C[1][j] = (rand()%q0);
        }*/
   

    MyIntFFT(c0_FFT, C[0]);

    for(i=0; i<N0; i++)
    {
        aux_FFT[i] = c0_FFT[i]*SKid_FFT[i];
    }

/*		cout << "MESSAGE b4 DECRYPT: "<<endl;
		for(int j=0; j<N0; j++)
        {
            cout << message[j] << " ";  
        }*/

    MyIntReverseFFT(message, aux_FFT);


    for(i=0; i<N0; i++)
    {
        message[i] = C[1][i] - message[i];
        message[i] = ((unsigned long)(message[i] ))%q0;
        message[i] = (message[i] + (q0>>2) )/(q0>>1);
        message[i] %= 2;
    }

}


//==============================================================================
//==============================================================================
//                             BENCHES AND TESTS
//                   FOR EXTRACTION AND ENCRYPTION/DECRYPTION
//==============================================================================
//==============================================================================


void Trapdoor_Bench(const unsigned int nb_extr, MSK_Data * MSKD)
{
    clock_t t1, t2;
    float diff;
    unsigned int i;
    vec_ZZ kw;
    ZZX SK_td[2];

    t1 = clock();

    cout << "0%" << flush;
    for(i=0; i<nb_extr; i++)
    {
        kw = RandomVector();

        PEKS_Trapdoor(SK_td, kw, MSKD);
        if((i+1)%(nb_extr/10)==0)
        {
            cout << "..." << (i+1)/(nb_extr/10) << "0%" << flush;
        }
    }

    t2 = clock();
    diff = ((float)t2 - (float)t1)/1000000.0F;
    cout << "\n\nIt took " << diff << " seconds to create  " << nb_extr << " trapdoors." << endl;
    cout << "That's " << (diff/nb_extr)*1000 << " milliseconds per trapdoor." << endl << endl;
}


void Encrypt_Bench(const unsigned int nb_cryp, MPK_Data * MPKD, MSK_Data * MSKD)
{
    clock_t te1, te2, td1, td2;
    float diffe, diffd;
    unsigned int i,j;
    vec_ZZ kw;
    ZZX SK_td[2], w;
    CC_t SKid_FFT[N0];
    long int message[N0], decrypted[N0];
    long int keyword[N0], Ciphertext[2][N0];


    kw = RandomVector();
    PEKS_Trapdoor(SK_td, kw, MSKD);
    PEKS_Verify_Trapdoor(SK_td, kw, MSKD);
    ZZXToFFT(SKid_FFT, SK_td[1]);

    for(i=0; i<N0; i++)
    {
        keyword[i] = conv<long int>(kw[i]);
    }

    


    cout << "0%" << flush ;
    for(i=0; i<nb_cryp; i++)
    {


	te1 = clock();	
		PEKS_Enc(Ciphertext, message, keyword, MPKD);
	te2 = clock();

	

	td1 = clock();
	/*	if (!PEKS_Test(decrypted, Ciphertext, SKid_FFT)){
			 cout << "TEST FAILED --- Exiting..."<<endl;
			break;
			}*/
			
	td2 = clock();
	
    //    if((i+1)%(nb_cryp/10)==0)
        {
            cout << "..." << (i+1)/(nb_cryp/10) << "0%" << flush;
        }

	diffe += ((float)te2 - (float)te1)/1000000.0l;
	diffd += ((float)td2 - (float)td1)/1000000.0l;

    }

    cout << "\n\nIt took " << diffe << " seconds to do " << nb_cryp << " encryptions." << endl;
    cout << "That's " << (diffe/nb_cryp)*1000 << " milliseconds per PEKS generation." << endl;
    cout << "That's " << (diffe/nb_cryp)*1000*1024/N0 << " milliseconds per PEKS per Kilobit." << endl << endl;

    cout << "\n\nIt took " << diffd << " seconds to do " << nb_cryp << " Tests." << endl;
    cout << "That's " << (diffd/nb_cryp)*1000 << " milliseconds per Tests." << endl;
    cout << "That's " << (diffd/nb_cryp)*1000*1024/N0 << " milliseconds per Tests per Kilobit." << endl << endl;

}


void Trapdoor_Test(const unsigned int nb_extr, MSK_Data * MSKD)
{
    unsigned int i, rep;
    vec_ZZ kw;
    ZZX SK_kw[2];

    rep = 0;

    cout << "0%" << flush;
    for(i=0; i<nb_extr; i++)
    {
        kw = RandomVector();

        PEKS_Trapdoor(SK_kw, kw, MSKD);
        rep += PEKS_Verify_Trapdoor(SK_kw, kw, MSKD);
      //  if((i+1)%(nb_extr/10)==0)
        {
            cout << "..." << (i+1)/(nb_extr/10) << "0%" << flush;
        }
    }

    cout << endl;
    if(rep == 0)
    {    cout << endl << nb_extr << " Trapdoor successfully performed!" << endl << endl;    }
    else
    {    cout << endl << rep << " out of " << nb_extr << " extractions failed miserabily!" << endl << endl;    }
}


void Encrypt_Test(const unsigned int nb_cryp, MPK_Data * MPKD, MSK_Data * MSKD)
{
    unsigned int i, j, rep;
    vec_ZZ kw;
    ZZX SK_td[2], m;
    CC_t SKtd_FFT[N0];
    long int kw0[N0], Ciphertext[2][N0], Ciphertext2[N0];
    long int message[N0], decrypted[N0];
	long keywordConv [N0];
	
	
	
/*		keywordConv[0] =  878974;
	keywordConv[1] = 11134;
	keywordConv[2] = 85012;
	keywordConv[3] = 546;
	keywordConv[4] = 1198876;
	keywordConv[5] = 171110;
	keywordConv[6] = 881000;
	keywordConv[7] = 0;
	keywordConv[8] =  100023 - 6619531;
	keywordConv[9] = 1000;
	keywordConv[10] = 0;
	keywordConv[11] =0;
	keywordConv[12] = 100257;
	keywordConv[13] = 0;
	keywordConv[14] = 0;
	keywordConv[15] = q0-55555;*/
	
	/*long jim[N0];*/
    //kw = RandomVector();
	
	//================
	int sum = 0;
	string word1; char ch1;
	char keywordAux1[N0];
	cout << "Keyin a word";
	cin >> word1;
	for  (int i=0; i < word1.length();i++){
		keywordAux1[i] = word1[i];
		ch1  = keywordAux1[i];
		keywordConv[i] = (ch1);
	}
	for (int i =word1.length(); i<N0;i++){
		keywordConv[i] = 0;
	}
		for (int i =0; i<N0;i++){
		sum +=keywordConv[i];
	}
	srand(sum);
			for (int i = 0; i<N0 ; i++){
	
	keywordConv[i] = (rand())%q0;
		}
	//==============
	
	
	
	kw = keywordVector(keywordConv);
  //kw = RandomVector();

    PEKS_Trapdoor(SK_td, kw, MSKD);
    PEKS_Verify_Trapdoor(SK_td, kw, MSKD);
    ZZXToFFT(SKtd_FFT, SK_td[1]);

    rep = 0;
	sum = 0;
	long keywordConverted[N0] ={0};
	string word; char ch;
	char keywordAux[N0];
	cout << "Keyin a word";
	cin >> word;
	for  (int i=0; i < word.length();i++){
		keywordAux[i] = word[i];
		ch  = keywordAux[i];
		keywordConverted[i] = (ch);
	}
	for (int i =word.length(); i<N0;i++){
		keywordConverted[i] = 0;
	}
	for (int i =word1.length(); i<N0;i++){
		keywordConverted[i] = 0;
	}
		for (int i =0; i<N0;i++){
		sum +=keywordConverted[i];
	}
	srand(sum);
			for (int i = 0; i<N0; i++){
	
	keywordConverted[i] = (rand())%q0;
		}
	

  /*  for(i=0; i<N0; i++)
    {
        kw0[i] = conv<long int>(kw[i]);
	

    }

    cout << "0%" << flush;*/
	

    for(i=0; i<nb_cryp; i++)
    {


		PEKS_Enc(Ciphertext,Ciphertext2,keywordConverted, MPKD);

		PEKS_Test(decrypted,Ciphertext, SKtd_FFT);

		for(j=0; j<N0; j++){
			if( Ciphertext2[j] != decrypted[j])
			{
				cout << "ERROR : Dec(Enc(m)) != m " << endl;
				rep++;
				break;
			}
		}

		  //  if((i+1)%(nb_cryp/10)==0)
			{
		   //     cout << "..." << (i+1)/(nb_cryp/10) << "0%" << flush;
			}
    }

    cout << endl;
    if(rep == 0)
    {    cout << endl << nb_cryp << " PEKS+TEST successfully performed!" << endl << endl;    }
    else
    {    cout << endl << rep << " out of " << nb_cryp << " PEKS+TEST failed miserabily!" << endl << endl;    }
}

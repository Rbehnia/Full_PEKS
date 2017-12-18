#ifndef LIBE_SCHEME_H
#define LIBE_SCHEME_H

#include "params.h"
#include "Sampling.h"
#include "FFT.h"
#include "Random.h"
#include "Algebra.h"

void Keygen(ZZ_pX& PublicKey, ZZX* PrivateKey);
void CompletePrivateKey(mat_ZZ& B, const ZZX * const PrivateKey);
void GPV(RR_t * v, const RR_t * const c, const RR_t s, const MSK_Data * const MSKD);
void CompleteMSK(MSK_Data * MSKD, ZZX * MSK);
void CompleteMPK(MPK_Data * MPKD, ZZ_pX MPK);
void PEKS_Trapdoor(ZZX SK_id[2], vec_ZZ id, const MSK_Data * const MSKD);
unsigned long IBE_Verify_Key(const ZZX SK_id[2], const vec_ZZ id, const MSK_Data * const MSKD);
void PEKS_Enc(long C[2][N0],  long C2[N0],  long id0[N0], const MPK_Data * const MPKD);
void PEKS_Test(long message[N0],  long C[2][N0], const CC_t * const SKid_FFT);
unsigned long  PEKS_Verify_Trapdoor( const ZZX SK_td[2], const vec_ZZ kw, const MSK_Data * const MSKD);
void Trapdoor_Bench(const unsigned int nb_extr, MSK_Data * MSKD);
void Encrypt_Bench(const unsigned int nb_cryp, MPK_Data * MPKD, MSK_Data * MSKD);
void Trapdoor_Test(const unsigned int nb_extr, MSK_Data * MSKD);
void Encrypt_Test(const unsigned int nb_cryp, MPK_Data * MPKD, MSK_Data * MSKD);

#endif

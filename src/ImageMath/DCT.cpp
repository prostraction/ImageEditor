#include "DCT.h"

const int32_t c1 = 1004,
              s1 = 200,
              c3 = 851,
              s3 = 569,
              r2c6 = 554,
              r2s6 = 1337,
              r2 = 181;

void DCT::doDCT(
        double *DCT_Matrix,
        const uint8_t *Image,
        const uint32_t &XPos,
        const uint32_t &YPos,
        const uint32_t &ImageWidth,
        const uint8_t &channels,
        const uint8_t &channelselected) {
    
    if (!Image)
        return;
    if (!DCT_Matrix)
        DCT_Matrix = new double[64];

    int32_t rows[8][8] {0};
    int32_t x[9] {0};

    /* transform rows */
    for (int32_t i = 0; i < 8; i++) {
        for (int32_t index = 0; index < 8; index) {
            x[index] = ImagePixel::GetPixel(Image, XPos+index, YPos+i, ImageWidth, channels, channelselected);
        }
        DCT_1D(x);
        rows[i][0] = x[6];
        rows[i][4] = x[4];
        rows[i][2] = x[8] >> 10;
        rows[i][6] = x[7] >> 10;
        rows[i][7] = (x[2] - x[5]) >> 10;
        rows[i][1] = (x[2] + x[5]) >> 10;
        rows[i][3] = (x[3] * r2) >> 17;
        rows[i][5] = (x[0] * r2) >> 17;
    }

    /* transform columns */
    for (int32_t i = 0; i < 8; i++) {
        for (int index = 0; index < 8; index++) {
            x[index] = rows[index][i];
        }
        DCT_1D(x);
        DCT_Matrix[i + 8 * 0] = (double)((x[6] + 16) >> 3);
        DCT_Matrix[i + 8 * 4] = (double)((x[4] + 16) >> 3);
        DCT_Matrix[i + 8 * 2] = (double)((x[8] + 16384) >> 13);
        DCT_Matrix[i + 8 * 6] = (double)((x[7] + 16384) >> 13);
        DCT_Matrix[i + 8 * 7] = (double)((x[2] - x[5] + 16384) >> 13);
        DCT_Matrix[i + 8 * 1] = (double)((x[2] + x[5] + 16384) >> 13);
        DCT_Matrix[i + 8 * 3] = (double)(((x[3] >> 8) * r2 + 8192) >> 12);
        DCT_Matrix[i + 8 * 5] = (double)(((x[0] >> 8) * r2 + 8192) >> 12);
    }
}
void DCT::doIDCT(
        const double *DCT_Matrix,
        uint8_t *Image,
        const uint32_t &XPos,
        const uint32_t &YPos,
        const uint32_t &ImageWidth,
        const uint8_t &channels,
        const uint8_t &channelselected) {

    const int32_t Scale[64] = {
         4096, 2276, 5352, 3218, 4096, 3218, 2217, 2276,
         2276, 1264, 2973, 1788, 2276, 1788, 1232, 1264,
         5352, 2973, 6992, 4205, 5352, 4205, 2896, 2973,
         3218, 1788, 4205, 2529, 3218, 2529, 1742, 1788,
         4096, 2276, 5352, 3218, 4096, 3218, 2217, 2276,
         3218, 1788, 4205, 2529, 3218, 2529, 1742, 1788,
         2217, 1232, 2896, 1742, 2217, 1742, 1200, 1232,
         2276, 1264, 2973, 1788, 2276, 1788, 1232, 1264,
    };

    static uint8_t ClipTable[3*256] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    };
    uint8_t *Clip = ClipTable + 256;

    int32_t* IDCT_Matrix     = new int32_t[64];
    int32_t* IDCT_Matrix_out = new int32_t[64];
    memset(IDCT_Matrix_out, 0, 64);

    for (int32_t i = 0; i < 64; i++)
        IDCT_Matrix[i] = (int32_t)DCT_Matrix[i];

    int32_t Row[64], Column[64];
    Row[0] = (IDCT_Matrix[0] + 4) * Scale[0];

    for (int32_t i = 1; i < 64; i++)
        Row[i] = IDCT_Matrix[i] * Scale[i];
    for (int32_t i = 0; i < 8; i++)
        IDCT_1D(Row + i*8, Column + i);
    for (int32_t i = 0; i < 8; i++)
        IDCT_1D(Column + i*8, Row + i);
    for (int32_t i = 0; i < 64; i++)
        IDCT_Matrix_out[i] = Clip[Row[i] >> 15];

    for (int32_t i = 0; i < 8; i++) {
        for (int32_t j = 0; j < 8; j++)
            Image[channelselected + (channels * ((j + XPos) + ImageWidth * (i+YPos)))] = IDCT_Matrix_out[8*i + j];
    }

    delete[] IDCT_Matrix;
    delete[] IDCT_Matrix_out;
    
    return;
}

void DCT::DCT_1D(int32_t x[9]) {
    /* Stage 1 */
    x[8] = x[7] + x[0];
    x[0] -= x[7];
    x[7] = x[1] + x[6];
    x[1] -= x[6];
    x[6] = x[2] + x[5];
    x[2] -= x[5];
    x[5] = x[3] + x[4];
    x[3] -= x[4];

    /* Stage 2 */
    x[4] = x[8] + x[5];
    x[8] -= x[5];
    x[5] = x[7] + x[6];
    x[7] -= x[6];
    x[6] = c1 * (x[1] + x[2]);
    x[2] = (-s1 - c1) * x[2] + x[6];
    x[1] = (s1 - c1) * x[1] + x[6];
    x[6] = c3 * (x[0] + x[3]);
    x[3] = (-s3 - c3) * x[3] + x[6];
    x[0] = (s3 - c3) * x[0] + x[6];

    /* Stage 3 */
    x[6] = x[4] + x[5];
    x[4] -= x[5];
    x[5] = r2c6 * (x[7] + x[8]);
    x[7] = (-r2s6 - r2c6) * x[7] + x[5];
    x[3] -= x[1];
    return;
}
void DCT::IDCT_1D(int32_t *F, int32_t *f) {
    int32_t p, n;
    p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5] * 45, n = F[3] * 45;
    F[5] = ( n + p + (p << 2) + F[5] ) >> 7;
    F[3] = ( n - p + (n << 2) + F[3] ) >> 7;

    p = F[1] << 8, n=F[7] << 8;
    F[1] = ( n + p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n - p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2] - p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];

    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];p = F[1] + F[7];
    n = F[1] - F[7];

    F[1] = p + F[3];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
    F[7] = n + F[5];
    F[5] = n - F[5];
    F[3] = p - F[3];

    p = F[5]*45, n= F[3]*45;
    F[5] = ( n+p + (p<<2) + F[5] ) >> 7;
    F[3] = ( n-p + (n<<2) + F[3] ) >> 7;

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];

    p =F[1]<<8, n=F[7] << 8;
    F[1] = ( n+p + (F[1]<<7) - F[1] ) >> 8;
    F[7] = ( n-p + (F[7]<<7) - F[7] ) >> 8;

    p = F[6];
    F[6] += F[2];
    F[2] = ((F[2]-p) * 181 >> 7) - F[6];

    p = F[0] + F[4];
    n = F[0] - F[4];
    F[0] = p + F[6];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
    F[4] = n + F[2];
    F[2] = n - F[2];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
    F[6] = p - F[6];


    f[0*8] = F[0] + F[1];
    f[1*8] = F[4] + F[5];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
    f[2*8] = F[2] + F[3];
    f[3*8] = F[6] + F[7];
    f[4*8] = F[6] - F[7];
    f[5*8] = F[2] - F[3];
    f[6*8] = F[4] - F[5];
    f[7*8] = F[0] - F[1];
}
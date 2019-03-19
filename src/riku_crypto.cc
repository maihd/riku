// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/core.h>
#include <riku/crypto.h>

#define MD5_F1(x, y, z) (z ^ (x & (y ^ z)))
#define MD5_F2(x, y, z) MD5_F1(z, x, y)
#define MD5_F3(x, y, z) (x ^ y ^ z)
#define MD5_F4(x, y, z) (y ^ (x | ~z))
#define MD5_STEP(f, w, x, y, z, data, s) ( w += f(x, y, z) + (data), w = w<<s | w>>(32-s), w += x )

namespace crypto
{
    static byte MD5_PADDING[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    static const u32 CRC32_TABLE[256] = {
        0x00000000U, 0x77073096U, 0xee0e612cU, 0x990951baU,
        0x076dc419U, 0x706af48fU, 0xe963a535U, 0x9e6495a3U,
        0x0edb8832U, 0x79dcb8a4U, 0xe0d5e91eU, 0x97d2d988U,
        0x09b64c2bU, 0x7eb17cbdU, 0xe7b82d07U, 0x90bf1d91U,
        0x1db71064U, 0x6ab020f2U, 0xf3b97148U, 0x84be41deU,
        0x1adad47dU, 0x6ddde4ebU, 0xf4d4b551U, 0x83d385c7U,
        0x136c9856U, 0x646ba8c0U, 0xfd62f97aU, 0x8a65c9ecU,
        0x14015c4fU, 0x63066cd9U, 0xfa0f3d63U, 0x8d080df5U,
        0x3b6e20c8U, 0x4c69105eU, 0xd56041e4U, 0xa2677172U,
        0x3c03e4d1U, 0x4b04d447U, 0xd20d85fdU, 0xa50ab56bU,
        0x35b5a8faU, 0x42b2986cU, 0xdbbbc9d6U, 0xacbcf940U,
        0x32d86ce3U, 0x45df5c75U, 0xdcd60dcfU, 0xabd13d59U,
        0x26d930acU, 0x51de003aU, 0xc8d75180U, 0xbfd06116U,
        0x21b4f4b5U, 0x56b3c423U, 0xcfba9599U, 0xb8bda50fU,
        0x2802b89eU, 0x5f058808U, 0xc60cd9b2U, 0xb10be924U,
        0x2f6f7c87U, 0x58684c11U, 0xc1611dabU, 0xb6662d3dU,
        0x76dc4190U, 0x01db7106U, 0x98d220bcU, 0xefd5102aU,
        0x71b18589U, 0x06b6b51fU, 0x9fbfe4a5U, 0xe8b8d433U,
        0x7807c9a2U, 0x0f00f934U, 0x9609a88eU, 0xe10e9818U,
        0x7f6a0dbbU, 0x086d3d2dU, 0x91646c97U, 0xe6635c01U,
        0x6b6b51f4U, 0x1c6c6162U, 0x856530d8U, 0xf262004eU,
        0x6c0695edU, 0x1b01a57bU, 0x8208f4c1U, 0xf50fc457U,
        0x65b0d9c6U, 0x12b7e950U, 0x8bbeb8eaU, 0xfcb9887cU,
        0x62dd1ddfU, 0x15da2d49U, 0x8cd37cf3U, 0xfbd44c65U,
        0x4db26158U, 0x3ab551ceU, 0xa3bc0074U, 0xd4bb30e2U,
        0x4adfa541U, 0x3dd895d7U, 0xa4d1c46dU, 0xd3d6f4fbU,
        0x4369e96aU, 0x346ed9fcU, 0xad678846U, 0xda60b8d0U,
        0x44042d73U, 0x33031de5U, 0xaa0a4c5fU, 0xdd0d7cc9U,
        0x5005713cU, 0x270241aaU, 0xbe0b1010U, 0xc90c2086U,
        0x5768b525U, 0x206f85b3U, 0xb966d409U, 0xce61e49fU,
        0x5edef90eU, 0x29d9c998U, 0xb0d09822U, 0xc7d7a8b4U,
        0x59b33d17U, 0x2eb40d81U, 0xb7bd5c3bU, 0xc0ba6cadU,
        0xedb88320U, 0x9abfb3b6U, 0x03b6e20cU, 0x74b1d29aU,
        0xead54739U, 0x9dd277afU, 0x04db2615U, 0x73dc1683U,
        0xe3630b12U, 0x94643b84U, 0x0d6d6a3eU, 0x7a6a5aa8U,
        0xe40ecf0bU, 0x9309ff9dU, 0x0a00ae27U, 0x7d079eb1U,
        0xf00f9344U, 0x8708a3d2U, 0x1e01f268U, 0x6906c2feU,
        0xf762575dU, 0x806567cbU, 0x196c3671U, 0x6e6b06e7U,
        0xfed41b76U, 0x89d32be0U, 0x10da7a5aU, 0x67dd4accU,
        0xf9b9df6fU, 0x8ebeeff9U, 0x17b7be43U, 0x60b08ed5U,
        0xd6d6a3e8U, 0xa1d1937eU, 0x38d8c2c4U, 0x4fdff252U,
        0xd1bb67f1U, 0xa6bc5767U, 0x3fb506ddU, 0x48b2364bU,
        0xd80d2bdaU, 0xaf0a1b4cU, 0x36034af6U, 0x41047a60U,
        0xdf60efc3U, 0xa867df55U, 0x316e8eefU, 0x4669be79U,
        0xcb61b38cU, 0xbc66831aU, 0x256fd2a0U, 0x5268e236U,
        0xcc0c7795U, 0xbb0b4703U, 0x220216b9U, 0x5505262fU,
        0xc5ba3bbeU, 0xb2bd0b28U, 0x2bb45a92U, 0x5cb36a04U,
        0xc2d7ffa7U, 0xb5d0cf31U, 0x2cd99e8bU, 0x5bdeae1dU,
        0x9b64c2b0U, 0xec63f226U, 0x756aa39cU, 0x026d930aU,
        0x9c0906a9U, 0xeb0e363fU, 0x72076785U, 0x05005713U,
        0x95bf4a82U, 0xe2b87a14U, 0x7bb12baeU, 0x0cb61b38U,
        0x92d28e9bU, 0xe5d5be0dU, 0x7cdcefb7U, 0x0bdbdf21U,
        0x86d3d2d4U, 0xf1d4e242U, 0x68ddb3f8U, 0x1fda836eU,
        0x81be16cdU, 0xf6b9265bU, 0x6fb077e1U, 0x18b74777U,
        0x88085ae6U, 0xff0f6a70U, 0x66063bcaU, 0x11010b5cU,
        0x8f659effU, 0xf862ae69U, 0x616bffd3U, 0x166ccf45U,
        0xa00ae278U, 0xd70dd2eeU, 0x4e048354U, 0x3903b3c2U,
        0xa7672661U, 0xd06016f7U, 0x4969474dU, 0x3e6e77dbU,
        0xaed16a4aU, 0xd9d65adcU, 0x40df0b66U, 0x37d83bf0U,
        0xa9bcae53U, 0xdebb9ec5U, 0x47b2cf7fU, 0x30b5ffe9U,
        0xbdbdf21cU, 0xcabac28aU, 0x53b39330U, 0x24b4a3a6U,
        0xbad03605U, 0xcdd70693U, 0x54de5729U, 0x23d967bfU,
        0xb3667a2eU, 0xc4614ab8U, 0x5d681b02U, 0x2a6f2b94U,
        0xb40bbe37U, 0xc30c8ea1U, 0x5a05df1bU, 0x2d02ef8dU
    }; 
    
    static const u64 CRC64_TABLE[256] = {
        0x0000000000000000ULL, 0x7ad870c830358979ULL,
        0xf5b0e190606b12f2ULL, 0x8f689158505e9b8bULL,
        0xc038e5739841b68fULL, 0xbae095bba8743ff6ULL,
        0x358804e3f82aa47dULL, 0x4f50742bc81f2d04ULL,
        0xab28ecb46814fe75ULL, 0xd1f09c7c5821770cULL,
        0x5e980d24087fec87ULL, 0x24407dec384a65feULL,
        0x6b1009c7f05548faULL, 0x11c8790fc060c183ULL,
        0x9ea0e857903e5a08ULL, 0xe478989fa00bd371ULL,
        0x7d08ff3b88be6f81ULL, 0x07d08ff3b88be6f8ULL,
        0x88b81eabe8d57d73ULL, 0xf2606e63d8e0f40aULL,
        0xbd301a4810ffd90eULL, 0xc7e86a8020ca5077ULL,
        0x4880fbd87094cbfcULL, 0x32588b1040a14285ULL,
        0xd620138fe0aa91f4ULL, 0xacf86347d09f188dULL,
        0x2390f21f80c18306ULL, 0x594882d7b0f40a7fULL,
        0x1618f6fc78eb277bULL, 0x6cc0863448deae02ULL,
        0xe3a8176c18803589ULL, 0x997067a428b5bcf0ULL,
        0xfa11fe77117cdf02ULL, 0x80c98ebf2149567bULL,
        0x0fa11fe77117cdf0ULL, 0x75796f2f41224489ULL,
        0x3a291b04893d698dULL, 0x40f16bccb908e0f4ULL,
        0xcf99fa94e9567b7fULL, 0xb5418a5cd963f206ULL,
        0x513912c379682177ULL, 0x2be1620b495da80eULL,
        0xa489f35319033385ULL, 0xde51839b2936bafcULL,
        0x9101f7b0e12997f8ULL, 0xebd98778d11c1e81ULL,
        0x64b116208142850aULL, 0x1e6966e8b1770c73ULL,
        0x8719014c99c2b083ULL, 0xfdc17184a9f739faULL,
        0x72a9e0dcf9a9a271ULL, 0x08719014c99c2b08ULL,
        0x4721e43f0183060cULL, 0x3df994f731b68f75ULL,
        0xb29105af61e814feULL, 0xc849756751dd9d87ULL,
        0x2c31edf8f1d64ef6ULL, 0x56e99d30c1e3c78fULL,
        0xd9810c6891bd5c04ULL, 0xa3597ca0a188d57dULL,
        0xec09088b6997f879ULL, 0x96d1784359a27100ULL,
        0x19b9e91b09fcea8bULL, 0x636199d339c963f2ULL,
        0xdf7adabd7a6e2d6fULL, 0xa5a2aa754a5ba416ULL,
        0x2aca3b2d1a053f9dULL, 0x50124be52a30b6e4ULL,
        0x1f423fcee22f9be0ULL, 0x659a4f06d21a1299ULL,
        0xeaf2de5e82448912ULL, 0x902aae96b271006bULL,
        0x74523609127ad31aULL, 0x0e8a46c1224f5a63ULL,
        0x81e2d7997211c1e8ULL, 0xfb3aa75142244891ULL,
        0xb46ad37a8a3b6595ULL, 0xceb2a3b2ba0eececULL,
        0x41da32eaea507767ULL, 0x3b024222da65fe1eULL,
        0xa2722586f2d042eeULL, 0xd8aa554ec2e5cb97ULL,
        0x57c2c41692bb501cULL, 0x2d1ab4dea28ed965ULL,
        0x624ac0f56a91f461ULL, 0x1892b03d5aa47d18ULL,
        0x97fa21650afae693ULL, 0xed2251ad3acf6feaULL,
        0x095ac9329ac4bc9bULL, 0x7382b9faaaf135e2ULL,
        0xfcea28a2faafae69ULL, 0x8632586aca9a2710ULL,
        0xc9622c4102850a14ULL, 0xb3ba5c8932b0836dULL,
        0x3cd2cdd162ee18e6ULL, 0x460abd1952db919fULL,
        0x256b24ca6b12f26dULL, 0x5fb354025b277b14ULL,
        0xd0dbc55a0b79e09fULL, 0xaa03b5923b4c69e6ULL,
        0xe553c1b9f35344e2ULL, 0x9f8bb171c366cd9bULL,
        0x10e3202993385610ULL, 0x6a3b50e1a30ddf69ULL,
        0x8e43c87e03060c18ULL, 0xf49bb8b633338561ULL,
        0x7bf329ee636d1eeaULL, 0x012b592653589793ULL,
        0x4e7b2d0d9b47ba97ULL, 0x34a35dc5ab7233eeULL,
        0xbbcbcc9dfb2ca865ULL, 0xc113bc55cb19211cULL,
        0x5863dbf1e3ac9decULL, 0x22bbab39d3991495ULL,
        0xadd33a6183c78f1eULL, 0xd70b4aa9b3f20667ULL,
        0x985b3e827bed2b63ULL, 0xe2834e4a4bd8a21aULL,
        0x6debdf121b863991ULL, 0x1733afda2bb3b0e8ULL,
        0xf34b37458bb86399ULL, 0x8993478dbb8deae0ULL,
        0x06fbd6d5ebd3716bULL, 0x7c23a61ddbe6f812ULL,
        0x3373d23613f9d516ULL, 0x49aba2fe23cc5c6fULL,
        0xc6c333a67392c7e4ULL, 0xbc1b436e43a74e9dULL,
        0x95ac9329ac4bc9b5ULL, 0xef74e3e19c7e40ccULL,
        0x601c72b9cc20db47ULL, 0x1ac40271fc15523eULL,
        0x5594765a340a7f3aULL, 0x2f4c0692043ff643ULL,
        0xa02497ca54616dc8ULL, 0xdafce7026454e4b1ULL,
        0x3e847f9dc45f37c0ULL, 0x445c0f55f46abeb9ULL,
        0xcb349e0da4342532ULL, 0xb1eceec59401ac4bULL,
        0xfebc9aee5c1e814fULL, 0x8464ea266c2b0836ULL,
        0x0b0c7b7e3c7593bdULL, 0x71d40bb60c401ac4ULL,
        0xe8a46c1224f5a634ULL, 0x927c1cda14c02f4dULL,
        0x1d148d82449eb4c6ULL, 0x67ccfd4a74ab3dbfULL,
        0x289c8961bcb410bbULL, 0x5244f9a98c8199c2ULL,
        0xdd2c68f1dcdf0249ULL, 0xa7f41839ecea8b30ULL,
        0x438c80a64ce15841ULL, 0x3954f06e7cd4d138ULL,
        0xb63c61362c8a4ab3ULL, 0xcce411fe1cbfc3caULL,
        0x83b465d5d4a0eeceULL, 0xf96c151de49567b7ULL,
        0x76048445b4cbfc3cULL, 0x0cdcf48d84fe7545ULL,
        0x6fbd6d5ebd3716b7ULL, 0x15651d968d029fceULL,
        0x9a0d8ccedd5c0445ULL, 0xe0d5fc06ed698d3cULL,
        0xaf85882d2576a038ULL, 0xd55df8e515432941ULL,
        0x5a3569bd451db2caULL, 0x20ed197575283bb3ULL,
        0xc49581ead523e8c2ULL, 0xbe4df122e51661bbULL,
        0x3125607ab548fa30ULL, 0x4bfd10b2857d7349ULL,
        0x04ad64994d625e4dULL, 0x7e7514517d57d734ULL,
        0xf11d85092d094cbfULL, 0x8bc5f5c11d3cc5c6ULL,
        0x12b5926535897936ULL, 0x686de2ad05bcf04fULL,
        0xe70573f555e26bc4ULL, 0x9ddd033d65d7e2bdULL,
        0xd28d7716adc8cfb9ULL, 0xa85507de9dfd46c0ULL,
        0x273d9686cda3dd4bULL, 0x5de5e64efd965432ULL,
        0xb99d7ed15d9d8743ULL, 0xc3450e196da80e3aULL,
        0x4c2d9f413df695b1ULL, 0x36f5ef890dc31cc8ULL,
        0x79a59ba2c5dc31ccULL, 0x037deb6af5e9b8b5ULL,
        0x8c157a32a5b7233eULL, 0xf6cd0afa9582aa47ULL,
        0x4ad64994d625e4daULL, 0x300e395ce6106da3ULL,
        0xbf66a804b64ef628ULL, 0xc5bed8cc867b7f51ULL,
        0x8aeeace74e645255ULL, 0xf036dc2f7e51db2cULL,
        0x7f5e4d772e0f40a7ULL, 0x05863dbf1e3ac9deULL,
        0xe1fea520be311aafULL, 0x9b26d5e88e0493d6ULL,
        0x144e44b0de5a085dULL, 0x6e963478ee6f8124ULL,
        0x21c640532670ac20ULL, 0x5b1e309b16452559ULL,
        0xd476a1c3461bbed2ULL, 0xaeaed10b762e37abULL,
        0x37deb6af5e9b8b5bULL, 0x4d06c6676eae0222ULL,
        0xc26e573f3ef099a9ULL, 0xb8b627f70ec510d0ULL,
        0xf7e653dcc6da3dd4ULL, 0x8d3e2314f6efb4adULL,
        0x0256b24ca6b12f26ULL, 0x788ec2849684a65fULL,
        0x9cf65a1b368f752eULL, 0xe62e2ad306bafc57ULL,
        0x6946bb8b56e467dcULL, 0x139ecb4366d1eea5ULL,
        0x5ccebf68aecec3a1ULL, 0x2616cfa09efb4ad8ULL,
        0xa97e5ef8cea5d153ULL, 0xd3a62e30fe90582aULL,
        0xb0c7b7e3c7593bd8ULL, 0xca1fc72bf76cb2a1ULL,
        0x45775673a732292aULL, 0x3faf26bb9707a053ULL,
        0x70ff52905f188d57ULL, 0x0a2722586f2d042eULL,
        0x854fb3003f739fa5ULL, 0xff97c3c80f4616dcULL,
        0x1bef5b57af4dc5adULL, 0x61372b9f9f784cd4ULL,
        0xee5fbac7cf26d75fULL, 0x9487ca0fff135e26ULL,
        0xdbd7be24370c7322ULL, 0xa10fceec0739fa5bULL,
        0x2e675fb4576761d0ULL, 0x54bf2f7c6752e8a9ULL,
        0xcdcf48d84fe75459ULL, 0xb71738107fd2dd20ULL,
        0x387fa9482f8c46abULL, 0x42a7d9801fb9cfd2ULL,
        0x0df7adabd7a6e2d6ULL, 0x772fdd63e7936bafULL,
        0xf8474c3bb7cdf024ULL, 0x829f3cf387f8795dULL,
        0x66e7a46c27f3aa2cULL, 0x1c3fd4a417c62355ULL,
        0x935745fc4798b8deULL, 0xe98f353477ad31a7ULL,
        0xa6df411fbfb21ca3ULL, 0xdc0731d78f8795daULL,
        0x536fa08fdfd90e51ULL, 0x29b7d047efec8728ULL,
    };

    static void md5_encode(byte* output, const u32* input, int len)
    {
        for (int i = 0, j = 0; j < len; i++, j += 4)
        {
            output[j + 0] = (byte)((input[i] >>  0) & 0xff);
            output[j + 1] = (byte)((input[i] >>  8) & 0xff);
            output[j + 2] = (byte)((input[i] >> 16) & 0xff);
            output[j + 3] = (byte)((input[i] >> 24) & 0xff);
        }
    }

    static void md5_decode(u32* output, const byte* input, int len)
    {
        for (int i = 0, j = 0; j < len; i++, j += 4)
        {
            output[i]  = (u32)(input[j + 0] <<  0);
            output[i] |= (u32)(input[j + 1] <<  8);
            output[i] |= (u32)(input[j + 2] << 16);
            output[i] |= (u32)(input[j + 3] << 24);
        }
    }

    static void md5_transform(u32 state[4], const byte block[64])
    {
        u32 a, b, c, d, x[16];

        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];

        md5_decode(x, block, 64);

        MD5_STEP(MD5_F1, a, b, c, d, x[ 0] + 0xd76aa478,  7);
        MD5_STEP(MD5_F1, d, a, b, c, x[ 1] + 0xe8c7b756, 12);
        MD5_STEP(MD5_F1, c, d, a, b, x[ 2] + 0x242070db, 17);
        MD5_STEP(MD5_F1, b, c, d, a, x[ 3] + 0xc1bdceee, 22);
        MD5_STEP(MD5_F1, a, b, c, d, x[ 4] + 0xf57c0faf,  7);
        MD5_STEP(MD5_F1, d, a, b, c, x[ 5] + 0x4787c62a, 12);
        MD5_STEP(MD5_F1, c, d, a, b, x[ 6] + 0xa8304613, 17);
        MD5_STEP(MD5_F1, b, c, d, a, x[ 7] + 0xfd469501, 22);
        MD5_STEP(MD5_F1, a, b, c, d, x[ 8] + 0x698098d8,  7);
        MD5_STEP(MD5_F1, d, a, b, c, x[ 9] + 0x8b44f7af, 12);
        MD5_STEP(MD5_F1, c, d, a, b, x[10] + 0xffff5bb1, 17);
        MD5_STEP(MD5_F1, b, c, d, a, x[11] + 0x895cd7be, 22);
        MD5_STEP(MD5_F1, a, b, c, d, x[12] + 0x6b901122,  7);
        MD5_STEP(MD5_F1, d, a, b, c, x[13] + 0xfd987193, 12);
        MD5_STEP(MD5_F1, c, d, a, b, x[14] + 0xa679438e, 17);
        MD5_STEP(MD5_F1, b, c, d, a, x[15] + 0x49b40821, 22);

        MD5_STEP(MD5_F2, a, b, c, d, x[ 1] + 0xf61e2562,  5);
        MD5_STEP(MD5_F2, d, a, b, c, x[ 6] + 0xc040b340,  9);
        MD5_STEP(MD5_F2, c, d, a, b, x[11] + 0x265e5a51, 14);
        MD5_STEP(MD5_F2, b, c, d, a, x[ 0] + 0xe9b6c7aa, 20);
        MD5_STEP(MD5_F2, a, b, c, d, x[ 5] + 0xd62f105d,  5);
        MD5_STEP(MD5_F2, d, a, b, c, x[10] + 0x02441453,  9);
        MD5_STEP(MD5_F2, c, d, a, b, x[15] + 0xd8a1e681, 14);
        MD5_STEP(MD5_F2, b, c, d, a, x[ 4] + 0xe7d3fbc8, 20);
        MD5_STEP(MD5_F2, a, b, c, d, x[ 9] + 0x21e1cde6,  5);
        MD5_STEP(MD5_F2, d, a, b, c, x[14] + 0xc33707d6,  9);
        MD5_STEP(MD5_F2, c, d, a, b, x[ 3] + 0xf4d50d87, 14);
        MD5_STEP(MD5_F2, b, c, d, a, x[ 8] + 0x455a14ed, 20);
        MD5_STEP(MD5_F2, a, b, c, d, x[13] + 0xa9e3e905,  5);
        MD5_STEP(MD5_F2, d, a, b, c, x[ 2] + 0xfcefa3f8,  9);
        MD5_STEP(MD5_F2, c, d, a, b, x[ 7] + 0x676f02d9, 14);
        MD5_STEP(MD5_F2, b, c, d, a, x[12] + 0x8d2a4c8a, 20);

        MD5_STEP(MD5_F3, a, b, c, d, x[ 5] + 0xfffa3942,  4);
        MD5_STEP(MD5_F3, d, a, b, c, x[ 8] + 0x8771f681, 11);
        MD5_STEP(MD5_F3, c, d, a, b, x[11] + 0x6d9d6122, 16);
        MD5_STEP(MD5_F3, b, c, d, a, x[14] + 0xfde5380c, 23);
        MD5_STEP(MD5_F3, a, b, c, d, x[ 1] + 0xa4beea44,  4);
        MD5_STEP(MD5_F3, d, a, b, c, x[ 4] + 0x4bdecfa9, 11);
        MD5_STEP(MD5_F3, c, d, a, b, x[ 7] + 0xf6bb4b60, 16);
        MD5_STEP(MD5_F3, b, c, d, a, x[10] + 0xbebfbc70, 23);
        MD5_STEP(MD5_F3, a, b, c, d, x[13] + 0x289b7ec6,  4);
        MD5_STEP(MD5_F3, d, a, b, c, x[ 0] + 0xeaa127fa, 11);
        MD5_STEP(MD5_F3, c, d, a, b, x[ 3] + 0xd4ef3085, 16);
        MD5_STEP(MD5_F3, b, c, d, a, x[ 6] + 0x04881d05, 23);
        MD5_STEP(MD5_F3, a, b, c, d, x[ 9] + 0xd9d4d039,  4);
        MD5_STEP(MD5_F3, d, a, b, c, x[12] + 0xe6db99e5, 11);
        MD5_STEP(MD5_F3, c, d, a, b, x[15] + 0x1fa27cf8, 16);
        MD5_STEP(MD5_F3, b, c, d, a, x[ 2] + 0xc4ac5665, 23);

        MD5_STEP(MD5_F4, a, b, c, d, x[ 0] + 0xf4292244,  6);
        MD5_STEP(MD5_F4, d, a, b, c, x[ 7] + 0x432aff97, 10);
        MD5_STEP(MD5_F4, c, d, a, b, x[14] + 0xab9423a7, 15);
        MD5_STEP(MD5_F4, b, c, d, a, x[ 5] + 0xfc93a039, 21);
        MD5_STEP(MD5_F4, a, b, c, d, x[12] + 0x655b59c3,  6);
        MD5_STEP(MD5_F4, d, a, b, c, x[ 3] + 0x8f0ccc92, 10);
        MD5_STEP(MD5_F4, c, d, a, b, x[10] + 0xffeff47d, 15);
        MD5_STEP(MD5_F4, b, c, d, a, x[ 1] + 0x85845dd1, 21);
        MD5_STEP(MD5_F4, a, b, c, d, x[ 8] + 0x6fa87e4f,  6);
        MD5_STEP(MD5_F4, d, a, b, c, x[15] + 0xfe2ce6e0, 10);
        MD5_STEP(MD5_F4, c, d, a, b, x[ 6] + 0xa3014314, 15);
        MD5_STEP(MD5_F4, b, c, d, a, x[13] + 0x4e0811a1, 21);
        MD5_STEP(MD5_F4, a, b, c, d, x[ 4] + 0xf7537e82,  6);
        MD5_STEP(MD5_F4, d, a, b, c, x[11] + 0xbd3af235, 10);
        MD5_STEP(MD5_F4, c, d, a, b, x[ 2] + 0x2ad7d2bb, 15);
        MD5_STEP(MD5_F4, b, c, d, a, x[ 9] + 0xeb86d391, 21);

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
    }

    static void md5_update(MD5* context, const byte* input, int length)
    {
        u32 i, index, part_len;

        // Compute number of bytes mod 64
        index = (u32)((context->count[0] >> 3) & 0x3F);

        // Update number of bits
        if ((context->count[0] += ((u32)length << 3))< ((u32)length << 3))
        {
            context->count[1]++;
        }

        context->count[1] += ((u32)length >> 29);

        part_len = 64 - index;

        // Transform as many times as possible.
        if (length >= part_len) 
        {
            memory::copy(&context->buffer[index], input, part_len);
            md5_transform(context->state, context->buffer);

            for (i = part_len; i + 63 < length; i += 64) 
            {
                md5_transform(context->state, &input[i]);
            }

            index = 0;
        } 
        else 
        {
            i = 0;
        }

        // Buffer remaining input
        memory::copy(&context->buffer[index], &input[i], length - i);
    }

    u32 md5(MD5& ctx, const void* buffer, int length)
    {
        // init
        ctx.state[0] = 0x67452301;
        ctx.state[1] = 0xefcdab89;
        ctx.state[2] = 0x98badcfe;
        ctx.state[3] = 0x10325476;

        ctx.count[0] = 0;
        ctx.count[1] = 0;

        // update
        md5_update(&ctx, (const byte*)buffer, length);

        // final
        byte  digest[16];
        byte  bits[8];
        u32   index, pad_len;

        // Save number of bits
        md5_encode(bits, ctx.count, 8);

        // Pad out to 56 mod 64.
        index = (unsigned int)((ctx.count[0] >> 3) & 0x3f);
        pad_len = (index < 56) ? (56 - index) : (120 - index);
        md5_update(&ctx, MD5_PADDING, pad_len);

        // Append length (before padding)
        md5_update(&ctx, bits, 8);
	
	    // Store state in digest
        md5_encode(digest, ctx.state, 16);

        u32 val = 
            (digest[ 3] << 24 | digest[ 2] << 16 | digest[ 1] << 8 | digest[ 0]) ^ 
			(digest[ 7] << 24 | digest[ 6] << 16 | digest[ 5] << 8 | digest[ 4]) ^
			(digest[11] << 24 | digest[10] << 16 | digest[ 9] << 8 | digest[ 8]) ^
            (digest[15] << 24 | digest[14] << 16 | digest[13] << 8 | digest[12]);

        return val;
    }

    u32 crc32(const void* buffer, int length)
    {
        return crc32(buffer, length, 0xffffffffU);
    }

    u32 crc32(const void* buffer, int length, u32 seed)
    {
        u32 res = seed;

        const byte* data = (const byte*)buffer;

        while (length-- > 0)
        {
            res = (res >> 8) ^ (CRC32_TABLE[(res ^ (*data++)) & 0xff]);
        }

        res = res ^ 0xffffffffU;
        return res;
    }

    u64 crc64(const void* buffer, int length)
    {
        return crc32(buffer, length, 0xffffffffffffffffULL);
    }

    u64 crc64(const void* buffer, int length, u64 seed)
    {
        u64 res = seed;

        const byte* data = (const byte*)buffer;

        while (length-- > 0)
        {
            res = (res >> 8) ^ (CRC32_TABLE[(res ^ (*data++)) & 0xff]);
        }

        res = res ^ 0xffffffffffffffffULL;
        return res;
    }

    u32 murmur32(const void* buffer, int length)
    {
        return murmur32(buffer, length, 0);
    }

    u64 murmur64(const void* buffer, int length)
    {
        return murmur64(buffer, length, 0);
    }

    // Compute hash value of buffer with Murmur algorithm
    u32 murmur32(const void* buffer, int length, u32 seed)
    {
        u32 h = (u32)seed;
        const u8* key = (const u8*)buffer;

        if (length > 3) 
        {
            const u32* key_x4 = (const u32*)key;
            usize i = length >> 2;

            do 
            {
                u32 k = *key_x4++;
                k *= 0xcc9e2d51;
                k  = (k << 15) | (k >> 17);
                k *= 0x1b873593;
                h ^= k;
                h  = (h << 13) | (h >> 19);
                h  = (h * 5) + 0xe6546b64;
            } while (--i);

            key = (const byte*) key_x4;
        }

        if (length & 3)
        {
            usize i = length & 3;
            u32 k = 0;
            key = &key[i - 1];

            do {
                k <<= 8;
                k  |= *key--;
            } while (--i);
            
            k *= 0xcc9e2d51;
            k  = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
        }

        h ^= length;
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

    u64 murmur64(const void* buffer, int length, u64 seed)
    {
        const u64 m = 0xc6a4a7935bd1e995ULL;
        const u32 r = 47;

        u64 h = seed;

        const u64* data = (const u64*)buffer;
        const u64* end = data + (u64)(length >> 3);

        while (data != end)
        {
#if CPU_BIG_ENDIAN
            u64 k = *data++;
            u8* p = (u8*)&k;
            u8 c;
            c = p[0]; p[0] = p[7]; p[7] = c;
            c = p[1]; p[1] = p[6]; p[6] = c;
            c = p[2]; p[2] = p[5]; p[5] = c;
            c = p[3]; p[3] = p[4]; p[4] = c;
#else
            u64 k = *data++;
#endif

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        const u8* data2 = (const u8*)data;

        switch (length & 7)
        {
        case 7: h ^= u64(data2[6]) << 48;
        case 6: h ^= u64(data2[5]) << 40;
        case 5: h ^= u64(data2[4]) << 32;
        case 4: h ^= u64(data2[3]) << 24;
        case 3: h ^= u64(data2[2]) << 16;
        case 2: h ^= u64(data2[1]) <<  8;
        case 1: h ^= u64(data2[0]) <<  0; h *= m;
        };

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }
}
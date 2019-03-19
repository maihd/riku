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

    static const u64 CRC32_TABLE[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
        0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
        0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
        0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
        0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
        0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
        0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
        0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
        0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
        0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
        0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
        0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
        0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
        0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
        0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
        0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
        0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
        0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
        0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
        0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
        0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
        0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
        0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
        0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
        0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
        0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
        0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
        0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
        0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
        0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
        0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
        0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
        0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
        0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
        0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
        0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
        0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
        0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
        0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
        0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
        0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
        0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    }; 
    
    static const u64 CRC64_TABLE[256] = {
        u64(0x0000000000000000), u64(0x7ad870c830358979),
        u64(0xf5b0e190606b12f2), u64(0x8f689158505e9b8b),
        u64(0xc038e5739841b68f), u64(0xbae095bba8743ff6),
        u64(0x358804e3f82aa47d), u64(0x4f50742bc81f2d04),
        u64(0xab28ecb46814fe75), u64(0xd1f09c7c5821770c),
        u64(0x5e980d24087fec87), u64(0x24407dec384a65fe),
        u64(0x6b1009c7f05548fa), u64(0x11c8790fc060c183),
        u64(0x9ea0e857903e5a08), u64(0xe478989fa00bd371),
        u64(0x7d08ff3b88be6f81), u64(0x07d08ff3b88be6f8),
        u64(0x88b81eabe8d57d73), u64(0xf2606e63d8e0f40a),
        u64(0xbd301a4810ffd90e), u64(0xc7e86a8020ca5077),
        u64(0x4880fbd87094cbfc), u64(0x32588b1040a14285),
        u64(0xd620138fe0aa91f4), u64(0xacf86347d09f188d),
        u64(0x2390f21f80c18306), u64(0x594882d7b0f40a7f),
        u64(0x1618f6fc78eb277b), u64(0x6cc0863448deae02),
        u64(0xe3a8176c18803589), u64(0x997067a428b5bcf0),
        u64(0xfa11fe77117cdf02), u64(0x80c98ebf2149567b),
        u64(0x0fa11fe77117cdf0), u64(0x75796f2f41224489),
        u64(0x3a291b04893d698d), u64(0x40f16bccb908e0f4),
        u64(0xcf99fa94e9567b7f), u64(0xb5418a5cd963f206),
        u64(0x513912c379682177), u64(0x2be1620b495da80e),
        u64(0xa489f35319033385), u64(0xde51839b2936bafc),
        u64(0x9101f7b0e12997f8), u64(0xebd98778d11c1e81),
        u64(0x64b116208142850a), u64(0x1e6966e8b1770c73),
        u64(0x8719014c99c2b083), u64(0xfdc17184a9f739fa),
        u64(0x72a9e0dcf9a9a271), u64(0x08719014c99c2b08),
        u64(0x4721e43f0183060c), u64(0x3df994f731b68f75),
        u64(0xb29105af61e814fe), u64(0xc849756751dd9d87),
        u64(0x2c31edf8f1d64ef6), u64(0x56e99d30c1e3c78f),
        u64(0xd9810c6891bd5c04), u64(0xa3597ca0a188d57d),
        u64(0xec09088b6997f879), u64(0x96d1784359a27100),
        u64(0x19b9e91b09fcea8b), u64(0x636199d339c963f2),
        u64(0xdf7adabd7a6e2d6f), u64(0xa5a2aa754a5ba416),
        u64(0x2aca3b2d1a053f9d), u64(0x50124be52a30b6e4),
        u64(0x1f423fcee22f9be0), u64(0x659a4f06d21a1299),
        u64(0xeaf2de5e82448912), u64(0x902aae96b271006b),
        u64(0x74523609127ad31a), u64(0x0e8a46c1224f5a63),
        u64(0x81e2d7997211c1e8), u64(0xfb3aa75142244891),
        u64(0xb46ad37a8a3b6595), u64(0xceb2a3b2ba0eecec),
        u64(0x41da32eaea507767), u64(0x3b024222da65fe1e),
        u64(0xa2722586f2d042ee), u64(0xd8aa554ec2e5cb97),
        u64(0x57c2c41692bb501c), u64(0x2d1ab4dea28ed965),
        u64(0x624ac0f56a91f461), u64(0x1892b03d5aa47d18),
        u64(0x97fa21650afae693), u64(0xed2251ad3acf6fea),
        u64(0x095ac9329ac4bc9b), u64(0x7382b9faaaf135e2),
        u64(0xfcea28a2faafae69), u64(0x8632586aca9a2710),
        u64(0xc9622c4102850a14), u64(0xb3ba5c8932b0836d),
        u64(0x3cd2cdd162ee18e6), u64(0x460abd1952db919f),
        u64(0x256b24ca6b12f26d), u64(0x5fb354025b277b14),
        u64(0xd0dbc55a0b79e09f), u64(0xaa03b5923b4c69e6),
        u64(0xe553c1b9f35344e2), u64(0x9f8bb171c366cd9b),
        u64(0x10e3202993385610), u64(0x6a3b50e1a30ddf69),
        u64(0x8e43c87e03060c18), u64(0xf49bb8b633338561),
        u64(0x7bf329ee636d1eea), u64(0x012b592653589793),
        u64(0x4e7b2d0d9b47ba97), u64(0x34a35dc5ab7233ee),
        u64(0xbbcbcc9dfb2ca865), u64(0xc113bc55cb19211c),
        u64(0x5863dbf1e3ac9dec), u64(0x22bbab39d3991495),
        u64(0xadd33a6183c78f1e), u64(0xd70b4aa9b3f20667),
        u64(0x985b3e827bed2b63), u64(0xe2834e4a4bd8a21a),
        u64(0x6debdf121b863991), u64(0x1733afda2bb3b0e8),
        u64(0xf34b37458bb86399), u64(0x8993478dbb8deae0),
        u64(0x06fbd6d5ebd3716b), u64(0x7c23a61ddbe6f812),
        u64(0x3373d23613f9d516), u64(0x49aba2fe23cc5c6f),
        u64(0xc6c333a67392c7e4), u64(0xbc1b436e43a74e9d),
        u64(0x95ac9329ac4bc9b5), u64(0xef74e3e19c7e40cc),
        u64(0x601c72b9cc20db47), u64(0x1ac40271fc15523e),
        u64(0x5594765a340a7f3a), u64(0x2f4c0692043ff643),
        u64(0xa02497ca54616dc8), u64(0xdafce7026454e4b1),
        u64(0x3e847f9dc45f37c0), u64(0x445c0f55f46abeb9),
        u64(0xcb349e0da4342532), u64(0xb1eceec59401ac4b),
        u64(0xfebc9aee5c1e814f), u64(0x8464ea266c2b0836),
        u64(0x0b0c7b7e3c7593bd), u64(0x71d40bb60c401ac4),
        u64(0xe8a46c1224f5a634), u64(0x927c1cda14c02f4d),
        u64(0x1d148d82449eb4c6), u64(0x67ccfd4a74ab3dbf),
        u64(0x289c8961bcb410bb), u64(0x5244f9a98c8199c2),
        u64(0xdd2c68f1dcdf0249), u64(0xa7f41839ecea8b30),
        u64(0x438c80a64ce15841), u64(0x3954f06e7cd4d138),
        u64(0xb63c61362c8a4ab3), u64(0xcce411fe1cbfc3ca),
        u64(0x83b465d5d4a0eece), u64(0xf96c151de49567b7),
        u64(0x76048445b4cbfc3c), u64(0x0cdcf48d84fe7545),
        u64(0x6fbd6d5ebd3716b7), u64(0x15651d968d029fce),
        u64(0x9a0d8ccedd5c0445), u64(0xe0d5fc06ed698d3c),
        u64(0xaf85882d2576a038), u64(0xd55df8e515432941),
        u64(0x5a3569bd451db2ca), u64(0x20ed197575283bb3),
        u64(0xc49581ead523e8c2), u64(0xbe4df122e51661bb),
        u64(0x3125607ab548fa30), u64(0x4bfd10b2857d7349),
        u64(0x04ad64994d625e4d), u64(0x7e7514517d57d734),
        u64(0xf11d85092d094cbf), u64(0x8bc5f5c11d3cc5c6),
        u64(0x12b5926535897936), u64(0x686de2ad05bcf04f),
        u64(0xe70573f555e26bc4), u64(0x9ddd033d65d7e2bd),
        u64(0xd28d7716adc8cfb9), u64(0xa85507de9dfd46c0),
        u64(0x273d9686cda3dd4b), u64(0x5de5e64efd965432),
        u64(0xb99d7ed15d9d8743), u64(0xc3450e196da80e3a),
        u64(0x4c2d9f413df695b1), u64(0x36f5ef890dc31cc8),
        u64(0x79a59ba2c5dc31cc), u64(0x037deb6af5e9b8b5),
        u64(0x8c157a32a5b7233e), u64(0xf6cd0afa9582aa47),
        u64(0x4ad64994d625e4da), u64(0x300e395ce6106da3),
        u64(0xbf66a804b64ef628), u64(0xc5bed8cc867b7f51),
        u64(0x8aeeace74e645255), u64(0xf036dc2f7e51db2c),
        u64(0x7f5e4d772e0f40a7), u64(0x05863dbf1e3ac9de),
        u64(0xe1fea520be311aaf), u64(0x9b26d5e88e0493d6),
        u64(0x144e44b0de5a085d), u64(0x6e963478ee6f8124),
        u64(0x21c640532670ac20), u64(0x5b1e309b16452559),
        u64(0xd476a1c3461bbed2), u64(0xaeaed10b762e37ab),
        u64(0x37deb6af5e9b8b5b), u64(0x4d06c6676eae0222),
        u64(0xc26e573f3ef099a9), u64(0xb8b627f70ec510d0),
        u64(0xf7e653dcc6da3dd4), u64(0x8d3e2314f6efb4ad),
        u64(0x0256b24ca6b12f26), u64(0x788ec2849684a65f),
        u64(0x9cf65a1b368f752e), u64(0xe62e2ad306bafc57),
        u64(0x6946bb8b56e467dc), u64(0x139ecb4366d1eea5),
        u64(0x5ccebf68aecec3a1), u64(0x2616cfa09efb4ad8),
        u64(0xa97e5ef8cea5d153), u64(0xd3a62e30fe90582a),
        u64(0xb0c7b7e3c7593bd8), u64(0xca1fc72bf76cb2a1),
        u64(0x45775673a732292a), u64(0x3faf26bb9707a053),
        u64(0x70ff52905f188d57), u64(0x0a2722586f2d042e),
        u64(0x854fb3003f739fa5), u64(0xff97c3c80f4616dc),
        u64(0x1bef5b57af4dc5ad), u64(0x61372b9f9f784cd4),
        u64(0xee5fbac7cf26d75f), u64(0x9487ca0fff135e26),
        u64(0xdbd7be24370c7322), u64(0xa10fceec0739fa5b),
        u64(0x2e675fb4576761d0), u64(0x54bf2f7c6752e8a9),
        u64(0xcdcf48d84fe75459), u64(0xb71738107fd2dd20),
        u64(0x387fa9482f8c46ab), u64(0x42a7d9801fb9cfd2),
        u64(0x0df7adabd7a6e2d6), u64(0x772fdd63e7936baf),
        u64(0xf8474c3bb7cdf024), u64(0x829f3cf387f8795d),
        u64(0x66e7a46c27f3aa2c), u64(0x1c3fd4a417c62355),
        u64(0x935745fc4798b8de), u64(0xe98f353477ad31a7),
        u64(0xa6df411fbfb21ca3), u64(0xdc0731d78f8795da),
        u64(0x536fa08fdfd90e51), u64(0x29b7d047efec8728),
    };

    static void md5_encode(byte* output, const uint* input, usize len)
    {
        usize i, j;
        for (i = 0, j = 0; j < len; i++, j += 4)
        {
            output[j + 0] = (byte)((input[i] >>  0) & 0xff);
            output[j + 1] = (byte)((input[i] >>  8) & 0xff);
            output[j + 2] = (byte)((input[i] >> 16) & 0xff);
            output[j + 3] = (byte)((input[i] >> 24) & 0xff);
        }
    }

    static void md5_decode(uint* output, const byte* input, usize len)
    {
        usize i, j;
        for (i = 0, j = 0; j < len; i++, j += 4)
        {
            output[i]  = (uint)(input[j + 0] <<  0);
            output[i] |= (uint)(input[j + 1] <<  8);
            output[i] |= (uint)(input[j + 2] << 16);
            output[i] |= (uint)(input[j + 3] << 24);
        }
    }

    static void md5_transform(uint state[4], const byte block[64])
    {
        uint a, b, c, d, x[16];

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

    static void md5_update(MD5* context, const byte* input, usize length)
    {
        ulong i, index, part_len;

        // Compute number of bytes mod 64
        index = (uint)((context->count[0] >> 3) & 0x3F);

        // Update number of bits
        if ((context->count[0] += ((ulong)length << 3))< ((ulong)length << 3))
        {
            context->count[1]++;
        }

        context->count[1] += ((ulong)length >> 29);

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

    u32 md5(MD5& ctx, const void* buffer, usize length)
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
        u64   index, pad_len;

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

        u64 val = 
            (digest[ 3] << 24 | digest[ 2] << 16 | digest[ 1] << 8 | digest[ 0]) ^ 
			(digest[ 7] << 24 | digest[ 6] << 16 | digest[ 5] << 8 | digest[ 4]) ^
			(digest[11] << 24 | digest[10] << 16 | digest[ 9] << 8 | digest[ 8]) ^
            (digest[15] << 24 | digest[14] << 16 | digest[13] << 8 | digest[12]);

        return val;
    }

    u32 crc32(const void* buffer, usize length)
    {
        u32 res = 0xffffffffU;

        const byte* data = (const byte*)buffer;

        while (length--) 
        {
            res = (res >> 8) ^ (CRC32_TABLE[(res ^ (*data++)) & 0xff]);
        }

        res = res ^ 0xffffffffU;
        return res;
    }

    u64 crc64(const void* buffer, usize length)
    {
        u32 res = 0xffffffffffffffffUL;

        const byte* data = (const byte*)buffer;

        while (length--)
        {
            res = (res >> 8) ^ (CRC32_TABLE[(res ^ (*data++)) & 0xff]);
        }

        res = res ^ 0xffffffffffffffffUL;
        return res;
    }

    u32 murmur32(const void* buffer, usize length)
    {
        return murmur32(buffer, length, 0);
    }

    u64 murmur64(const void* buffer, usize length)
    {
        return murmur64(buffer, length, 0);
    }

    // Compute hash value of buffer with Murmur algorithm
    u32 murmur32(const void* buffer, usize length, u32 seed)
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

    u64 murmur64(const void* buffer, usize length, u64 seed)
    {
        const u64 m = 0xc6a4a7935bd1e995ULL;
        const u32 r = 47;

        u64 h = seed;

        const u64* data = (const u64*)buffer;
        const u64* end = data + (length >> 3);

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
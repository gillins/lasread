
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint8_t lasread_u8(FILE *fh)
{
    uint8_t val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

uint16_t lasread_u16(FILE *fh)
{
    uint16_t val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

uint32_t lasread_u32(FILE *fh)
{
    uint32_t val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

uint64_t lasread_u64(FILE *fh)
{
    uint64_t val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

float lasread_float(FILE *fh)
{
    float val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

double lasread_double(FILE *fh)
{
    double val;
    fread(&val, sizeof(val), 1, fh);
    return val;
}

void lasread_chars(FILE *fh, int len, char *pszData)
{
    fread(pszData, sizeof(char), len, fh);
    pszData[len] = '\0';
}

int main(int argc, char *argv[])
{
    if( argc != 2 )
    {
        fprintf(stderr, "usage: lasfile\n");
        return 1;
    }

    FILE *fh = fopen(argv[1], "rb");
    if( fh == NULL )
    {
        fprintf(stderr, "Unable to read %s\n", argv[1]);
        return 1;
    }
    
    char szBuffer[128];
    
    lasread_chars(fh, 4, szBuffer);
    printf("Signature: %s\n", szBuffer);
    
    uint16_t nFileSourceId = lasread_u16(fh);
    printf("File Source ID: %hu\n", nFileSourceId);

    uint16_t nGlobalEncoding = lasread_u16(fh);
    printf("Global Encoding ID: %"PRIu16"\n", nGlobalEncoding);
    
    uint32_t nGUID1 = lasread_u32(fh);
    printf("GUID 1: %"PRIu32"\n", nGUID1);

    uint16_t nGUID2 = lasread_u16(fh);
    printf("GUID 2: %"PRIu32"\n", nGUID2);

    uint16_t nGUID3 = lasread_u16(fh);
    printf("GUID 3: %"PRIu32"\n", nGUID3);
    
    uint8_t nGUID4;
    for( int c = 0; c < 8; c++ )
    {
        nGUID4 = lasread_u8(fh);
        printf("GUID 4 pt %d %"PRIu8"\n", c, nGUID4);
    }
    
    uint8_t nVersionMajor = lasread_u8(fh);
    uint8_t nVersionMinor = lasread_u8(fh);
    printf("Version: %"PRIu8".%"PRIu8"\n", nVersionMajor, nVersionMinor);
    
    lasread_chars(fh, 32, szBuffer);
    printf("System Id: %s\n", szBuffer);

    lasread_chars(fh, 32, szBuffer);
    printf("Generating Software: %s\n", szBuffer);
    
    uint16_t nFileCreationDay = lasread_u16(fh);
    uint16_t nFileCreationYear = lasread_u16(fh);
    printf("File Creation Day/Year: %"PRIu16" %"PRIu16"\n", nFileCreationDay, nFileCreationYear);
    
    uint16_t nHeaderSize = lasread_u16(fh);
    printf("Header Size: %"PRIu16"\n", nHeaderSize);
    
    uint32_t nOffsetPointData = lasread_u32(fh);
    printf("Offset to point data: %"PRIu32"\n", nOffsetPointData);
    
    uint32_t nVarLengthRecs = lasread_u32(fh);
    printf("Number of Variable Length Records: %"PRIu32"\n", nVarLengthRecs);
    
    uint8_t nPointRecordFormat = lasread_u8(fh);
    printf("Point Data Record Format: %"PRIu8"\n", nPointRecordFormat);

    uint16_t nPointRecordLength = lasread_u16(fh);
    printf("Point Data Record Length: %"PRIu16"\n", nPointRecordLength);
    
    uint32_t nLegacyNPointRecords = lasread_u32(fh);
    printf("Legacy Number of point records: %"PRIu32"\n", nLegacyNPointRecords);
    
    uint32_t nLegacyPointsByReturn;
    for( int c = 0; c < 5; c++ )
    {
        nLegacyPointsByReturn = lasread_u32(fh);
        printf("Legacy Points By return %d : %"PRIu32"\n", c, nLegacyPointsByReturn);
    }
    
    double dXScale = lasread_double(fh);
    double dYScale = lasread_double(fh);
    double dZScale = lasread_double(fh);
    printf("Scale Factors (x, y, z): %f %f %f\n", dXScale, dYScale, dZScale);

    double dXOffset = lasread_double(fh);
    double dYOffset = lasread_double(fh);
    double dZOffset = lasread_double(fh);
    printf("Offset Factors (x, y, z): %f %f %f\n", dXOffset, dYOffset, dZOffset);
    
    double dMaxX = lasread_double(fh);
    double dMinX = lasread_double(fh);
    printf("X Range (min, max): %f %f\n", dMinX, dMaxX);

    double dMaxY = lasread_double(fh);
    double dMinY = lasread_double(fh);
    printf("Y Range (min, max): %f %f\n", dMinY, dMaxY);

    double dMaxZ = lasread_double(fh);
    double dMinZ = lasread_double(fh);
    printf("Z Range (min, max): %f %f\n", dMinZ, dMaxZ);
    
    uint64_t nStartOffWaveforms = lasread_u64(fh);
    printf("Start of Waveforms: %"PRIu64"\n", nStartOffWaveforms);

    uint64_t nStartEVLR = lasread_u64(fh);
    printf("Start of Extended Variable Length Records: %"PRIu64"\n", nStartEVLR);
    
    uint32_t nNumEVLR = lasread_u32(fh);
    printf("Number of Extended Variable Length Records: %"PRIu32"\n", nNumEVLR);
    
    uint64_t nNumPoints = lasread_u64(fh);
    printf("Number of points: %"PRIu64"\n", nNumPoints);
    
    uint64_t nNumPointsByReturn;
    for( int c = 0; c < 15; c++ )
    {
        nNumPointsByReturn = lasread_u64(fh);
        printf("Points By return %d : %"PRIu64"\n", c, nNumPointsByReturn);
    }
    
    
    fclose(fh);

    return 0;
}

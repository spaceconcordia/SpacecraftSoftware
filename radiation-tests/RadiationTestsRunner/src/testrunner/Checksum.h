#ifndef RADIATIONTESTSRUNNER_CHECKSUM_H
#define RADIATIONTESTSRUNNER_CHECKSUM_H
class checksum {
public:
    checksum() { clear(); }
    void clear() { sum = 0; r = 55665; c1 = 52845; c2 = 22719;}
    void add(DWORD w);
    void add(BOOL w) { add((DWORD)w); }
    void add(UINT w) { add((DWORD)w); }
    void add(WORD w);
    void add(const CString & s);
    void add(LPBYTE b, UINT length);
    void add(BYTE b);
    DWORD get() { return sum; }
protected:
    WORD r;
    WORD c1;
    WORD c2;
    DWORD sum;
};
#endif //RADIATIONTESTSRUNNER_CHECKSUM_H

import math

###Setting1
CT = 'HRDKHUBHAAMAEQMTMZSHGBAKFUBHAASYRXUNKYUAATQCTLUTOGEWVAJGVEIIYTKIOTQRXXQVSQLISVVOCNGCUXPKPIUBOHTVKCFKWNJSEZYSSUTUOESIXKAPVFXNZHAOQTLCGYJVAEHLNNKEESQMKSHKKDFCNZSRHRDKHSDKFXVPTGMKRUPZBIKEVNYEKXMFXKFYMWYUDZDENEWNKDAOUXGPCXZDLCSNFGCMCSNUAOJDBLQTAHEWYZCHQJYKSNUWOKQKONZGOKDXGUXKEMWQMCFGUEAVKHDIIATCHVTGYMGKJMLNPCNAYKMIRWEETIYQKELEGLQOVKISFNUDAJQIQYBXQTMZSHGBAKFZRCNWRSODAFKKXWGAZGDBIUDDHCUDFRFOVSZXADSHYSGLTQBMNEMKDCFSOZSRDYLIHIAXCMGMFEIDNZKOVJEOIEFNWWQEDRLZYZIZXADSHYSGLJYFWDUAKSIOGOZOXWYPBUFEPNBIRJUJNDZJJYMURKNCIKPWLRMRIAGVSXTYNIWPROHLDHQOMBEKZURQCLQOVKISFNUAFQBHGPCLHZTPJVPXIZKLQSNVKIJAEITTNVSVWNFYVATDEMKDCTGIHKZTVGZYXTYQEDBACFMNCAHRDKHSDKFXZXXGMJOSLPSZBMOILMMWRALAFFMNXXDYFBIYQVVOHSWKGBIRJGTBYQLKIJAEQBTAXGFGAVUIJADHQKLFWRJXYFVIGGQZNBHSUIYOZALSKIABLWQNXNXKOAJAIKHXODXWORVDOGBMHOPLQJZALQJZALIKTKLENZHQAVYUEUFEVLUXHGOWNMGWXUIAHGQOMNCKFQLIPBNKVWDLNGMJCOBFKIGBYWPAHMMPQLUTOGECXITZVVAJEOIDCNWMFNLOBGQXCYFWQFWVXWRKWYGBFHJVLBAWBOUQEKHZHSZZIZARYITDCLQFPGBTJMQVSQLIHPEJONCYMZWTVJVZOBOMOHPSXMPUKVAGXIPOQUQUQBCKXZJSZAHEWYHAEMKOJCCCFBEUKVNCAWANSNXISVVOWHQGQFBGWKQEGBIFRGIZUJQWIMFANTGBHWGVAGXIPOQUQTTRMWDHDGRFENKYPZVCLNQAUBTZSRYGVGOWSVROENABMZTOHZRQFUEVPLLIODEYRYLUTOGPYAFHJFIVOSFMPBSHLEKWYWJYTFYETAZQCRFTFHOMACOQVTWKLKYMGIMQDSYNWMFNIEITWMBVVWANBQFVUSKZOTLCCWABAGHWZBZHRDKHDTUOMUUUGQICHNUUQFJYUCQUO'
n, m, d = 1285, 257, 5
CT_number = [0 for _ in range(n)]
for i in range(n):
    CT_number[i] = ord(CT[i]) - 65

###Setting2
def IML(P):
    im = 0
    leng = len(P)
    for i in range(26):
        if P.count(i) != 0:
            im = im + (P.count(i) / leng) * math.log((P.count(i) / leng), 2)
    return -im

def dec(ct, k):
    pt = [0 for i in range(m)]
    for i in range(m):
        for j in range(d):
            pt[i] = (pt[i] + ct[i][j] * k[j]) % 26
    return pt

def num_to_str(pt):
    p = ''
    for i in range(len(pt)):
        p = p + chr(pt[i] + 97)
    return p

C = [0 for _ in range(m)]
for i in range(m):
    C[i] = CT_number[5 * i : 5 * (i + 1)]

###
P = [0 for i in range(n)]

K = [[3, 19, 11, 2, 3], [17, 24, 13, 11, 21], [12, 18, 4, 9, 0], [9, 7, 12, 20, 13], [18, 12, 6, 16, 23]]

for i in range(m):
    for j in range(d):
        for k in range(5):
            P[5 * i + j] = (P[5 * i + j] + (C[i][k] * K[j][k])) % 26

print(num_to_str(P))

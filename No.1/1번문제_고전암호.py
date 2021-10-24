import math
import copy

###Setting1
CT = 'HRDKHUBHAAMAEQMTMZSHGBAKFUBHAASYRXUNKYUAATQCTLUTOGEWVAJGVEIIYTKIOTQRXXQVSQLISVVOCNGCUXPKPIUBOHTVKCFKWNJSEZYSSUTUOESIXKAPVFXNZHAOQTLCGYJVAEHLNNKEESQMKSHKKDFCNZSRHRDKHSDKFXVPTGMKRUPZBIKEVNYEKXMFXKFYMWYUDZDENEWNKDAOUXGPCXZDLCSNFGCMCSNUAOJDBLQTAHEWYZCHQJYKSNUWOKQKONZGOKDXGUXKEMWQMCFGUEAVKHDIIATCHVTGYMGKJMLNPCNAYKMIRWEETIYQKELEGLQOVKISFNUDAJQIQYBXQTMZSHGBAKFZRCNWRSODAFKKXWGAZGDBIUDDHCUDFRFOVSZXADSHYSGLTQBMNEMKDCFSOZSRDYLIHIAXCMGMFEIDNZKOVJEOIEFNWWQEDRLZYZIZXADSHYSGLJYFWDUAKSIOGOZOXWYPBUFEPNBIRJUJNDZJJYMURKNCIKPWLRMRIAGVSXTYNIWPROHLDHQOMBEKZURQCLQOVKISFNUAFQBHGPCLHZTPJVPXIZKLQSNVKIJAEITTNVSVWNFYVATDEMKDCTGIHKZTVGZYXTYQEDBACFMNCAHRDKHSDKFXZXXGMJOSLPSZBMOILMMWRALAFFMNXXDYFBIYQVVOHSWKGBIRJGTBYQLKIJAEQBTAXGFGAVUIJADHQKLFWRJXYFVIGGQZNBHSUIYOZALSKIABLWQNXNXKOAJAIKHXODXWORVDOGBMHOPLQJZALQJZALIKTKLENZHQAVYUEUFEVLUXHGOWNMGWXUIAHGQOMNCKFQLIPBNKVWDLNGMJCOBFKIGBYWPAHMMPQLUTOGECXITZVVAJEOIDCNWMFNLOBGQXCYFWQFWVXWRKWYGBFHJVLBAWBOUQEKHZHSZZIZARYITDCLQFPGBTJMQVSQLIHPEJONCYMZWTVJVZOBOMOHPSXMPUKVAGXIPOQUQUQBCKXZJSZAHEWYHAEMKOJCCCFBEUKVNCAWANSNXISVVOWHQGQFBGWKQEGBIFRGIZUJQWIMFANTGBHWGVAGXIPOQUQTTRMWDHDGRFENKYPZVCLNQAUBTZSRYGVGOWSVROENABMZTOHZRQFUEVPLLIODEYRYLUTOGPYAFHJFIVOSFMPBSHLEKWYWJYTFYETAZQCRFTFHOMACOQVTWKLKYMGIMQDSYNWMFNIEITWMBVVWANBQFVUSKZOTLCCWABAGHWZBZHRDKHDTUOMUUUGQICHNUUQFJYUCQUO'

n, m, d = 1285, 257, 5

CT_number = [0 for _ in range(n)]
for i in range(n):
    CT_number[i] = ord(CT[i]) - 65

C = [0 for _ in range(m)]
for i in range(m):
    C[i] = CT_number[5 * i : 5 * (i + 1)]

letter_fre = [8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074]
log_letter_fre = [math.log(i / 100, 2) for i in letter_fre]
    
###Setting2
def IC(P):
    ic = 0
    leng = len(P)
    for i in range(26):
        ic = ic + (P.count(i) / leng) * (letter_fre[i] / 100)
    return ic
    
def IML(P):
    im = 0
    leng = len(P)
    for i in range(26):
        im = im + (P.count(i) / leng) * log_letter_fre[i]
    return -im

def dec(ct, k):
    pt = [0 for i in range(m)]
    for i in range(m):
        for j in range(d):
            pt[i] = (pt[i] + ct[i][j] * k[j]) % 26
    return pt

def check(k):
    k_2 = []
    k_13 = []
    for i in range(5):
        k_2.append(k[i] % 2)
        k_13.append(k[i] % 13)
    if set(k_2) == {0} or set(k_13) == {0}:
        return False
    else:
        return True

###
K = [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
I = [0, 0, 0, 0, 0]

x = [0, 0, 0, 0, 1]
while x != [25, 25, 25, 25, 25]:
    P = dec(C, x)
    ic = IC(P)
    if ic > min(I):
        if check(x):
            i = I.index(min(I))
            K[i] = copy.deepcopy(x)
            I[i] = copy.deepcopy(ic)
    x[4] = x[4] + 1
    for i in range(5):
        if x[4 - i] == 26:
            x[4 - i] = 0
            x[4 - i - 1] = x[4 - i - 1] + 1

print(K)

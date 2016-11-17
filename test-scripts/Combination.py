import sys
from itertools import combinations
import json

try:
    file_input = sys.argv[1]
    folder_ouput = sys.argv[2] + '/'
except:
    sys.exit("Run : combination.py input.json folder_ouput")
with open(file_input, 'r') as f:
     json_content = json.load(f)
wifiAPs = json_content["wifiAccessPoints"]

# for i in range (2, len(wifiAP)+1):
#     result_list = map(list, combinations(wifiAP, i))[0]
#     print result_list

num_wifiAP = len(wifiAPs)
dict_wifiAP = {i: wifiAPs[i] for i in range(num_wifiAP)}
# print dict_wifiAP


range_max = 2**num_wifiAP
x = [2**i for i in range(0, num_wifiAP)]
for i in range(1, range_max):
    if i not in x:
        bin_number = bin(i)[2:].zfill(num_wifiAP)
        json_wifiAP = {"wifiAccessPoints": []}
        for j in range(num_wifiAP):
            if str(bin_number[j])=='1':
                json_wifiAP["wifiAccessPoints"] += [dict_wifiAP[j]]
        file_output = folder_ouput + str(i) + '_tmp.json'
        with open(file_output, 'w') as f:
            data = json.dumps(json_wifiAP, ensure_ascii=False, encoding='utf8')
            f.write(unicode(data))
    # break
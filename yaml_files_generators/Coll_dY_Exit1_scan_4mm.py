import os
import re

from __init__ import *

exp_dir = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/Exit1_dY_scan_4mm"
run_dir_base = "Run"
id_pattern = re.compile(".*%s(\d+).*" % run_dir_base)

# dictionary of pairs Run ID --> collimator position (mm)
coll_exit1_Y1 = {37: 0,
                 38: 1.999,
                 39: 4.001,
                 40: 5.992,
                 41: 7.994,
                 42: 9.000,
                 43: 10.000
                 }

coll_exit1_Y2 = {37: 0,
                 38: 2.003,
                 39: 4.000,
                 40: 6.027,
                 41: 8.000,
                 42: 9.017,
                 43: 10.002
                 }

# other fields
magnetic_field = 6.5 # A
U_MCPPMT = 3400 # V
polarity = -1

# entrance
Entrance_Y1 = 0
Entrance_Y2 = 0
Entrance_X3 = 9.500
Entrance_X4 = 9.500

# exit 1
Exit1_X3 = 4.991
Exit1_X4 = 4.990

yaml_dict = {params_names['polarity']: polarity,
             params_names["magnet_current"]: magnetic_field,
             params_names['U_MCPPMT']: U_MCPPMT,
             params_names['entrance_dX']: entrance_full_dX - Entrance_X3 - Entrance_X4,
             params_names['entrance_dY']: entrance_full_dY - Entrance_Y1 - Entrance_Y2,
             params_names['exit1_dX']: exit1_full_dX - Exit1_X3 - Exit1_X4
             }

dirs = [d for d in os.listdir(exp_dir) if run_dir_base in d]
for d in dirs:
    m = id_pattern.match(d)
    if m:
        run_id = int(m.group(1))
        with open(os.path.join(exp_dir, d, 'run_info.yaml'), 'w+') as info_file:
            # run specific parameters
#             info_file.write("%s: %s" % (params_names["id"], run_id))
            info_file.write("%s: %s\n" % (params_names["id"], run_id))
            info_file.write("%s: %s\n" % (params_names["exit1_dY"], exit1_full_dY - coll_exit1_Y1[run_id] - coll_exit1_Y2[run_id]))
            for k in yaml_dict:
                info_file.write("%s: %s\n" % (k, yaml_dict[k]))






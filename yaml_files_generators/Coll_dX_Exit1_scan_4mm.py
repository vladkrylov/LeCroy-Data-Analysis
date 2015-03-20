import os
import re

from __init__ import *

exp_dir = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/Exit1_dX_scan_4mm"
run_dir_base = "Run"
id_pattern = re.compile(".*%s(\d+).*" % run_dir_base)

# dictionary of pairs Run ID --> collimator position (mm)
coll_exit1_X3 = {23: 0,
                 24: 0.997,
                 25: 1.997,
                 26: 2.994,
                 27: 3.994,
                 28: 4.973,
                 29: 5.990,
                 30: 6.993,
                 31: 7.997,
                 32: 8.498,
                 33: 8.997,
                 34: 9.498,
                 35: 9.703
                 }

coll_exit1_X4 = {23: 0,
                 24: 1.015,
                 25: 1.987,
                 26: 3.033,
                 27: 3.995,
                 28: 4.992,
                 29: 6.011,
                 30: 6.992,
                 31: 7.995,
                 32: 8.485,
                 33: 9.000,
                 34: 9.488,
                 35: 9.689
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
Exit1_Y1 = 0
Exit1_Y2 = 0

yaml_dict = {params_names['polarity']: polarity,
             params_names["magnet_current"]: magnetic_field,
             params_names['U_MCPPMT']: U_MCPPMT,
             params_names['entrance_dX']: entrance_full_dX - Entrance_X3 - Entrance_X4,
             params_names['entrance_dY']: entrance_full_dY - Entrance_Y1 - Entrance_Y2,
             params_names['exit1_dY']: exit1_full_dY - Exit1_Y1 - Exit1_Y2
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
            info_file.write("%s: %s\n" % (params_names["exit1_dX"], exit1_full_dX - coll_exit1_X3[run_id] - coll_exit1_X4[run_id]))
            for k in yaml_dict:
                info_file.write("%s: %s\n" % (k, yaml_dict[k]))






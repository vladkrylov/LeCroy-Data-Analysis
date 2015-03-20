import os
import re

from __init__ import *

exp_dir = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/B_scan_100um"
run_dir_base = "Run"
id_pattern = re.compile(".*%s(\d+).*" % run_dir_base)

# dictionary of pairs Run ID --> Magnet Current (A)
magnetic_field = {13: 11.0,
                  14: 10.9,
                  15: 10.8,
                  16: 10.7,
                  17: 10.6,
                  18: 10.5,
                  19: 10.4,
                  20: 10.3,
                  21: 10.2,
                  22: 10.1,
                  23: 10.0,
                  24: 9.9,
                  25: 9.8,
                  26: 9.7,
                  27: 9.6,
                  28: 9.5,
                  29: 9.4,
                  30: 9.3,
                  31: 9.2,
                  32: 9.0,
                  33: 8.5}

# other fields
U_MCPPMT = 2700 # V
polarity = -1

# entrance
Entrance_Y1 = 0
Entrance_Y2 = 0
Entrance_X3 = 0
Entrance_X4 = 0

# exit 1
Exit1_Y1 = 0
Exit1_Y2 = 0
Exit1_X3 = 0
Exit1_X4 = 0

yaml_dict = {params_names['polarity']: polarity,
             params_names['entrance_dX']: entrance_full_dX - Entrance_X3 - Entrance_X4,
             params_names['entrance_dY']: entrance_full_dY - Entrance_Y1 - Entrance_Y2,
             params_names['exit1_dX']: exit1_full_dX - Exit1_X3 - Exit1_X4,
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
            info_file.write("%s: %s\n" % (params_names["magnet_current"], magnetic_field[run_id]))
            for k in yaml_dict:
                info_file.write("%s: %s\n" % (k, yaml_dict[k]))






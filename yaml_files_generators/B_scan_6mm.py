import os
import re

from __init__ import *

exp_dir = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/B_scan_6mm"
run_dir_base = "Run"
id_pattern = re.compile(".*%s(\d+).*" % run_dir_base)

# dictionary of pairs Run ID --> Magnet Current (A)
magnetic_field = {1: 5.2,
                  2: 5.1,
                  3: 5.0,
                  4: 4.9,
                  5: 4.8,
                  6: 4.7,
                  7: 4.6,
                  8: 4.4,
                  9: 4.2,
                  10: 4.0,
                  11: 3.8,
                  12: 3.6,
                  13: 3.4,
                  14: 3.2,
                  15: 3.0}

# other fields
U_MCPPMT = 3400 # V
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
             params_names['U_MCPPMT']: U_MCPPMT,
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






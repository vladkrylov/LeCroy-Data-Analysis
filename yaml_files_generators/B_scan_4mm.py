import os
import re

from __init__ import *

exp_dir = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/B_scan_4mm"
run_dir_base = "Run"
id_pattern = re.compile(".*%s(\d+).*" % run_dir_base)

# dictionary of pairs Run ID --> Magnet Current (A)
magnetic_field = {2: 7.5,
                  3: 7.2,
                  4: 7.0,
                  5: 6.8,
                  6: 6.6,
                  7: 6.4,
                  8: 6.2,
                  9: 6.0,
                  10: 5.8,
                  11: 5.6,
                  12: 5.4,
                  13: 5.2,
                  14: 5.0,
                  15: 4.8,
                  16: 4.6,
                  17: 4.4,
                  18: 4.2,
                  19: 4.0,
                  20: 3.8,
                  21: 3.6}

# other fields
U_MCPPMT = 0 # V
polarity = -1

# entrance
Entrance_Y1 = 0
Entrance_Y2 = 0
Entrance_X3 = 5.551
Entrance_X4 = 5.484

# exit 1
Exit1_Y1 = 0
Exit1_Y2 = 0
Exit1_X3 = 5.494
Exit1_X4 = 5.516

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






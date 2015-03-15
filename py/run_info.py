import os

def get_member_type(s):
    """returns a type of given argument (either float or char*)"""
    try:
        float(s)
        return 'float'
    except ValueError:
        return 'char*'
    
def get_var_dict(yaml_filename=None):
    """returns a dictionary of member_name: member_type for all fields of yaml_filename"""
    if not os.path.isfile(yaml_filename):
        print "get_var_dict error: file %s does not exists" % yaml_filename
        return None
    
    d = {}
    with open(yaml_filename, 'r') as ya:
        for line in ya:
            k, v = line.split()
            
            k = k.strip(':')
            v_type = get_member_type(v)
            d[k] = v_type
            
    return d
    
def write_header(dir, memb_dict):
    # header
    with open(os.path.join(dir, 'RunInfo.h'), "w") as h_file:
        h_file.write(
"""#ifndef RUNINFO_H_
#define RUNINFO_H_
 
#include "TObject.h"
 
class RunInfo : public TObject {
public:
    RunInfo();
    virtual ~RunInfo();
    
""")
        for k in memb_dict:
            h_file.write("    void Set_%s(%s val);\n" % (k, memb_dict[k]))
            h_file.write("    %s Get_%s() const;\n\n" % (memb_dict[k], k))
            
            
        h_file.write("private:\n")
        for k in memb_dict:
            h_file.write("    %s %s;\n" % (memb_dict[k], k))
        
         
        h_file.write(
"""    
    ClassDef(RunInfo, 1)
};

#endif /* RUNINFO_H_ */
""")
    
def write_source(dir, memb_dict):
    # source
    with open(os.path.join(dir, 'RunInfo.cxx'), "w") as cpp_file:
        cpp_file.write(
"""#include "RunInfo.h"

#include <iostream>

ClassImp(RunInfo)

RunInfo::RunInfo() {

}

RunInfo::~RunInfo() {

}
""")
        for k in memb_dict:
            cpp_file.write(
"""
void RunInfo::Set_%s(%s val) {
    %s = val;
}
""" % (k, memb_dict[k], k))
            
            cpp_file.write(
"""
%s RunInfo::Get_%s() const {
    return %s;
}
""" % (memb_dict[k], k, k))
            
def create_params_class(dir='../root_scripts', par_dict=None):
    """creates source and header file with appropriate class of parameters"""
    write_header(dir, par_dict)
    write_source(dir, par_dict)
#     for k in par_dict:
#         write_member(dir, par_dict[k], k)
    
    
if __name__ == "__main__":
    params_file = "/home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis/test_data/Run10/run_info.yaml"
    params = get_var_dict(params_file)
    create_params_class(dir="/home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis/root_scripts", par_dict=params)



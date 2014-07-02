/*
 * File:      example_parentage.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity and cross section 
 *            for EM_MX_SH trigger in derived files
 *            for an explanation see ../doc/example_xsec.html
 * Created:   30-Jul-2003 - Petr Homola
 * Modified:  16-Nov-2003 - Petr Homola
 */

#include "lm_access/LumFileMap.hpp"

using namespace std;
using namespace lm_access;



int main() {
    LmAccessInterface::InterfaceType="stage3";
    lm_access::TriggerMap triggers;
    triggers["JT_65TT"] =  0;
    triggers["min_bias"] = 1;
    
    LumBlkMap lbn_map;

    cout << endl << "************* example of accessing information in stage3 files ****************" << endl << endl;
    
    lbn_map.read(1802999, 1802999, triggers);

    cout << endl << "*** file 1 ***" << endl;
    cout << endl << "selected triggers and releases info:" << endl << endl;

    lbn_map[1802999].print(cout);

    cout << endl;

    cout << "luml1 : " << lbn_map[1802999].luml1(triggers["min_bias"]) << endl;
    cout << "lumRecorded : " << lbn_map[1802999].luminosity(triggers["min_bias"],lm_access::Recorded) << endl;
    cout << "lumDelivered : " << lbn_map[1802999].luminosity(triggers["min_bias"],lm_access::Delivered) << endl;
    cout << "accepts (L1, L2, L3) : " << lbn_map[1802999].acceptsL1(triggers["min_bias"]) << " " << lbn_map[1802999].acceptsL2(triggers["min_bias"]) << " " << lbn_map[1802999].acceptsL3(triggers["min_bias"]) << " " << endl;
    cout << "status: " << lbn_map[1802999].status(triggers["min_bias"],lm_access::Reconstructed, LumFileRelease("tmb p13.05.00 p13.05.00")) << endl << endl;

    lbn_map.read(1050562, 1050562, triggers);

    cout << endl << "*** file 2 ***" << endl;
    cout << endl << "selected triggers and releases info:" << endl << endl;

    lbn_map[1050562].print(cout);

    cout << endl;

    cout << "luml1 : " << lbn_map[1050562].luml1(triggers["JT_65TT"]) << endl;
    cout << "lumRecorded : " << lbn_map[1050562].luminosity(triggers["JT_65TT"],lm_access::Recorded) << endl;
    cout << "lumDelivered : " << lbn_map[1050562].luminosity(triggers["JT_65TT"],lm_access::Delivered) << endl;
    cout << "accepts (L1, L2, L3) : " << lbn_map[1050562].acceptsL1(triggers["JT_65TT"]) << " " << lbn_map[1050562].acceptsL2(triggers["JT_65TT"]) << " " << lbn_map[1050562].acceptsL3(triggers["JT_65TT"]) << " " << endl;
    cout << "status: " << lbn_map[1050562].status(triggers["JT_65TT"],lm_access::Reconstructed, LumFileRelease("tmb p13.05.00 p13.05.00")) << endl << endl;
    
    lbn_map.read(1618631, 1618631, triggers);


    cout << endl << "*** file 3 ***" << endl;
    cout << endl << "selected triggers and releases info:" << endl << endl;

    lbn_map[1618631].print(cout);

    cout << endl;

    cout << "luml1 : " << lbn_map[1618631].luml1(triggers["JT_65TT"]) << endl;
    cout << "lumReconstructed : " << lbn_map[1618631].luminosity(triggers["JT_65TT"],lm_access::Reconstructed) << endl;
    cout << "lumDelivered : " << lbn_map[1618631].luminosity(triggers["JT_65TT"],lm_access::Delivered) << endl;
    cout << "accepts (L1, L2, L3) : " << lbn_map[1618631].acceptsL1(triggers["JT_65TT"]) << " " << lbn_map[1618631].acceptsL2(triggers["JT_65TT"]) << " " << lbn_map[1618631].acceptsL3(triggers["JT_65TT"]) << " " << endl;
    cout << "status: " << lbn_map[1618631].status(triggers["JT_65TT"],lm_access::Reconstructed, LumFileRelease("tmb p13.05.00 p13.05.00")) << endl << endl;

    return 0;
}


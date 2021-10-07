#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdint.h>
// #include <emscripten/bind.h>
// #include <emscripten/val.h>



double bias2[200] = {-0.0633006, -0.0418159, -0.0292446, -0.0323065, 0.00221278, -0.0278404, -0.00791415, 0.0124632, 0.030351, -0.00484282, -0.0460673, -0.0026825, 0.0294806, -0.0413984, -0.0060944, 0.00281647, -0.0619822, -0.00374689, -0.0157603, 0.0818672, 0.0143995, 0.0267434, -0.0112351, -0.016749, -0.00245278, 0.00130963, -0.0416777, -0.00542217, 0.0425161, 0.00493176, -0.0795951, -0.0302055, -0.0366191, 0.0374089, 0.0118828, -0.0190014, 0.0421214, -0.0231519, -0.00211014, 0.00476896, 0.00580436, -0.00717958, 0.0264596, 0.0077013, -0.0388625, -0.0138198, -0.0315171, -0.0570684, -0.0130602, -0.0229921, -0.0433778, -0.0617789, -0.0387618, -0.0769713, -0.00489525, -0.00641164, -0.0132602, 0.0306565, -0.0520935, -0.00726957, 0.0278002, -0.0337394, -0.00501575, 0.016234, 0.0167014, -0.0180725, -0.043352, -0.0526436, 0.0256309, -0.0265647, -0.00803962, -0.0264755, -0.0188262, 0.0314631, -0.0672101, 0.0127842, -0.00206525, 0.0287476, -0.000386656, 0.0014221, 0.00780434, -0.00299454, -0.014739, 0.0038017, -0.0101926, -0.010871, 0.00412415, 0.00188518, 0.0410688, -0.00500294, -0.023415, -0.0329038, -0.0413629, -0.0138103, 0.0146244, 0.0120582, 2.80456e-05, -0.0155289, -0.00892651, -0.0355384, -0.0309591, -0.0322386, -0.0109248, 0.00630611, -0.0418586, 0.00939031, -0.0259257, 0.00656013, 0.0197991, 0.00307299, -0.0434023, -0.027037, -0.0185477, -0.0124305, 0.000381289, 0.00802051, -0.0403603, -0.00308617, 0.0378199, -0.0347361, 0.00502067, 0.0503896, -0.0168651, -0.0106661, 5.73335e-07, -0.00123949, 0.000490727, -0.0177619, 0.00690026, -0.00516103, 0.0247955, -0.00728451, -0.0420092, 0.0306911, -0.0336546, -0.0569515, -0.00651976, 0.00154402, 0.0265394, -0.0211394, 0.0119942, -0.00266765, -0.0399261, -0.0265902, -0.0032733, -0.0162165, 0.0171161, -0.0214966, -0.0558496, -0.0141408, -0.0530243, 0.0313306, -0.0325508, 0.0293212, -0.0128736, 0.00676127, -0.0308541, -0.0438594, -0.0210305, -0.023505, -0.0242789, -0.0365151, -0.0264361, 0.00518916, -0.019748, -0.0342612, -0.0125643, -0.0410482, -0.0265985, -0.00707559, -0.0126861, 0.0520124, -0.0229763, -0.0381632, -0.0379556, 0.0369291, -0.00277884, 0.00246002, -0.0221447, -0.00434961, -0.0520586, 0.00445966, -0.00761488, -0.000651425, -0.0318532, -0.0343559, -0.0223518, -0.0487809, 0.0204658, 0.00793036, -0.00254415, -0.0583817, -0.0273782, -0.048006, 0.00121273, 0.0503765, -0.0137381, -0.0257147, 0.0156179, -0.0292101};        
double w23[10][200] = { {-0.139793, -0.477111, 0.968662, 0.199668, -0.698777, 0.307143, 0.0279934, -0.848355, -0.296762, 1.01322, -0.191288, -0.119681, -0.961365, 0.0136072, -0.416159, 0.0997103, 0.315833, 0.0612401, -0.40221, -0.450719, 0.507878, -0.09869, -0.0198644, -0.140265, 0.940342, -0.527403, -0.891728, -0.0388091, -0.219689, 0.117237, -0.408991, 0.322722, -0.489296, -0.501049, 0.33301, 0.192367, -0.336322, -1.49708, -0.909313, -0.320038, -0.423908, -0.300805, 0.601675, -0.61779, -0.279042, -0.503977, -0.0766383, -0.401519, 1.00133, 0.1185, -0.117198, -0.316498, -0.119842, 0.892946, 1.03031, 0.470468, 0.259965, -0.0240608, -0.295278, 1.36739, 0.452884, -0.100071, -0.405861, 0.27555, -0.703324, 0.23523, -1.08824, 0.165275, 0.588807, 0.816108, 0.431349, 0.610116, 0.0342929, -0.519468, -0.075653, 0.212503, -0.234073, 0.416817, -0.473024, -1.39945, -0.457228, 0.332319, 0.865959, -0.154173, 0.500903, 0.0252676, 1.34743, -1.2929, -0.275722, -0.299564, 0.559794, -0.368843, -0.901357, -0.478652, -0.0416708, 0.890573, -0.905647, -1.52343, 0.84726, 0.632725, -0.0962008, 0.581089, 1.22475, 0.495384, -0.639709, 0.379996, 0.163795, 0.303897, -0.134439, -0.261461, -0.234244, 0.174306, -0.420067, 0.045612, -0.547918, 1.39534, -1.15943, -0.478278, 1.69647, -0.420482, -0.341503, -0.175403, -0.297848, 0.483895, 0.818724, 0.588882, 0.752094, 0.272686, -0.648219, 0.0301056, -0.67376, 0.846821, -1.69417, 0.454459, 0.828545, -0.319582, 0.42109, -0.520012, 0.798765, 0.427391, -0.586831, -0.627701, -1.36072, 0.872604, -0.450239, -0.258902, -0.600663, 0.904407, -0.676107, 0.659755, 0.187042, -0.674706, -0.695517, 0.124483, 1.38327, -0.193305, -0.397121, -0.180319, -0.689569, -0.288903, 0.239187, -0.38465, 0.495592, 0.761038, -1.22222, 0.0997624, 1.28199, -0.0670625, 0.375893, -0.844885, -0.968484, 0.170502, 1.16473, 0.677956, 1.07418, 0.0107028, -1.52764, -1.27521, -0.440836, -0.0383615, 1.24812, 1.00306, 1.27404, -0.0930946, -0.304479, 0.571217, -0.468867, -0.16698, -0.41998, -0.150577, -0.524036, 0.393582, 0.518694, -1.43495, -0.718117, 0.792123, 0.798979, -0.912688, -0.443364, -0.375733},          {0.304754, 0.269081, 0.264522, 0.414693, -0.39226, 1.91309, -0.370434, 0.77411, -0.119913, -0.0985047, 0.689253, 1.10781, 0.827898, 0.256647, 0.0344712, 0.855875, 0.106225, -0.135558, -0.0198272, 0.241695, -0.659911, 0.513311, 1.28233, -0.207915, -0.401885, 0.292834, 1.40424, -0.655056, -0.353995, -0.00100707, 0.17208, 0.086163, 1.49347, -0.144056, 0.00178677, -0.326828, -0.412235, -0.521287, -0.388277, 0.914696, 0.16948, -0.328991, -0.104653, -1.40163, 0.646064, -0.298951, 0.460061, 0.07315, -0.216904, -0.453683, 1.15653, -0.0464007, 0.660686, 0.496037, 0.0125955, -0.0385647, 0.964335, 0.106112, -0.443696, 0.239286, 0.302955, 1.29982, -0.358477, -1.42289, -0.363323, -0.0669708, -0.356635, 1.34494, 0.970549, -0.0770597, -0.116623, -0.206408, 0.242729, -0.220379, 0.643578, -0.51797, -0.0470364, 0.680756, 0.621526, -0.679341, 0.760527, -0.252595, 0.140876, -0.432774, 0.727153, -0.0783817, 0.839838, -0.865212, 1.81216, -0.428106, 0.611114, 0.735791, 0.846871, -0.30357, -0.309605, -0.473679, -1.00342, 0.478954, 0.26766, 0.44728, -0.150691, -0.254211, -1.21677, -0.795543, 1.17023, -0.716864, 0.270931, -0.470756, 0.449304, -0.828904, 0.148373, -1.04043, 0.0251869, 0.250406, 0.901505, -0.198967, 1.52463, -0.0436414, -0.394999, 0.119514, -0.273616, -0.0450401, 1.14338, -1.09583, -0.872145, 1.14933, -0.93175, -1.002, -0.57502, 1.21766, 1.24033, 0.0590013, 0.932125, -0.570576, -0.425137, 0.503866, 0.271601, -0.680878, -1.02357, -0.272075, 0.0447457, -0.036966, 0.159427, 1.65019, 0.651154, 0.549846, -0.0834896, -0.540753, -0.110546, 1.70037, -0.623097, -0.785732, 0.774548, -0.290609, -0.440544, -0.308453, 0.207827, 1.01724, 0.177571, 0.73474, 1.51678, 1.05247, -0.581656, -0.201847, 0.790865, -0.397969, -0.169108, -0.227951, -0.677182, -0.197466, -0.995607, -0.5253, -0.554731, -0.594742, 0.113108, 0.320801, -0.125819, 0.0580191, 0.622499, -0.611121, -0.510527, -0.248473, 1.33129, -0.0718169, -0.137572, -1.43398, -0.640696, 1.77122, 0.835204, -0.327614, -0.730584, -0.289211, -0.113082, 0.595933, -0.0323759, -0.0499489, 0.731996, 1.35712, -0.294616, 0.649991},          {0.803623, 1.17304, 0.561872, -0.016884, -1.00296, 0.222203, -0.045032, 0.801224, -1.36779, 0.16361, -0.502975, 0.619164, -0.688084, 1.7798, -0.47348, 0.891788, -0.481627, 0.0494837, -0.140385, 0.597672, 0.124903, 0.933367, -0.415646, -0.974257, 0.775806, -0.0338375, 0.764153, -0.456352, 2.42467, -0.128578, 0.343089, 0.37428, -0.701786, -0.442572, -0.31642, 0.326007, -1.20923, -0.785775, 0.871617, 1.88609, -0.119116, -0.446219, -0.150965, -1.23089, 0.371502, -1.86494, 0.622719, 0.173074, -1.53666, -0.574735, -1.25476, -0.386958, 0.243452, 0.584791, -0.147187, -0.460584, 0.731943, -0.0217775, 0.251717, 1.07654, -0.353132, -0.0655343, 0.0815451, -0.00344465, 1.11046, 0.42518, -0.288052, -0.508844, -1.53124, -0.144874, 1.27169, 2.47814, -0.304599, -0.195208, -1.45147, 1.16037, -0.209091, -0.134263, -0.533839, 1.82407, -0.0157954, 0.667913, -1.10197, 0.784782, 0.728735, -0.0982775, 1.76375, -0.0499415, -1.0275, 1.44544, -0.730576, 0.540586, 0.738213, -0.598578, 1.54391, 1.3391, 1.63366, -1.40529, 1.22518, 0.716116, -0.301933, 0.0038178, -0.444347, -0.722806, 0.733065, -0.750174, 0.00751045, 0.883601, -0.277321, -0.433176, 0.836288, -0.340492, 0.110349, -2.40961, 2.00425, 1.24445, -1.52505, -0.560361, 0.625873, 0.73428, -0.082725, 0.191048, -0.309441, 0.603344, 1.19363, -1.27854, -0.819017, -0.555098, 0.409912, -0.639186, -0.817231, 0.210437, 0.363415, -1.82058, -0.347816, -0.870546, 0.654985, 1.34535, -1.32448, -1.78286, -0.417404, 0.683243, 1.78034, -1.53032, -0.00174717, 1.61006, 0.983348, 0.0885827, -0.642847, 0.0567395, 0.705879, 0.417084, -0.246788, -1.06335, 0.739168, -0.0496275, 0.975072, 0.0341619, 0.671308, 0.159355, -1.28224, -0.418236, 0.0932551, -0.341046, -0.55067, -1.28138, -0.446189, -0.203003, 0.215013, 1.13125, -0.152072, 0.112436, 0.572514, 0.642482, 0.462967, -0.696297, -0.158994, -1.94561, -0.221868, 1.64065, 0.847196, -1.3663, 0.63604, 0.379266, 0.165263, -0.651112, 1.3993, 1.823, -1.33417, 0.0100496, -0.0977016, -1.19836, -0.42513, 0.0703146, 0.460319, 1.06706, -0.451721, 0.316518, -0.57594, 0.505103},          {1.16632, 1.03028, 0.431822, -0.665313, 0.164747, -0.119608, -0.50185, 1.21965, 1.78564, -0.505557, 1.81282, -0.172269, 0.100223, -0.409718, -1.44889, -0.689841, -0.228298, -0.834079, -0.233982, 0.334037, -1.33578, 0.193935, 1.14985, -0.226806, 0.518421, -1.08244, 0.912432, 1.10644, 0.0521834, -1.20501, 0.611619, -0.15715, -1.94914, -0.335694, -0.824951, 0.340436, -0.460302, 0.376065, 0.0810795, 0.679882, -0.123678, 0.485871, 0.244458, 1.8076, -0.431837, -1.46607, 1.13301, 0.121046, -0.206387, 0.438837, -1.20389, 1.27396, -0.978963, -0.917981, -0.931456, -0.115278, 1.38839, -0.663333, 0.328308, -0.923092, 0.754259, 0.242821, 0.445027, 1.6712, -0.362469, -1.15737, 1.93336, -0.765757, 0.34639, -1.196, -0.326904, -0.332782, 0.468648, -0.49629, -0.399699, 0.0214471, 0.0803717, -0.379277, 1.87049, 1.51442, 1.1111, 4.5002e-05, -0.996927, 1.54248, -1.70052, 0.0238487, 0.721562, -0.73316, 0.408254, 0.30905, -1.65253, -1.74074, 0.486436, -0.308023, 0.550199, -0.19196, -0.0784092, 1.792, -1.6794, -0.00041633, -0.438662, -1.20943, -0.508436, -1.42107, -0.721686, 0.0611689, -1.20715, 1.03558, 0.537243, 0.626569, 0.278124, 1.8612, 0.454492, 0.435179, -0.354136, -0.621117, -1.46472, -1.87006, 0.0683362, 0.561615, -0.875157, -0.421144, -0.868183, 0.236449, 0.43423, 1.22992, 0.373985, -0.180644, -0.187702, -0.0178437, 1.13695, 0.651426, -0.445808, 1.83048, 0.35438, -0.627683, 0.378682, 2.30654, -0.481043, -0.548404, 1.06792, 0.137226, -0.601869, -0.250049, 1.67814, -0.0172731, -0.543161, -0.178031, 0.389175, 0.248959, -0.0661897, -0.859047, 1.2241, 2.18126, 0.883437, 0.323063, -0.303207, 0.654761, 0.958199, 0.478676, 0.0677112, -0.352356, -0.835593, 0.168807, -0.552631, 0.33374, -0.623855, 0.128983, 1.31326, -0.335979, -1.02238, 0.456507, -1.33862, -0.520551, -1.59009, -0.0542935, -0.0747806, 0.0777059, -0.0450919, 1.00897, -0.731702, -0.521826, -1.17146, 2.16528, 0.3356, 1.17062, 0.52721, -1.01082, 0.711727, 0.583456, 1.03338, -1.27895, 0.758045, -0.542756, 1.87249, -0.590006, 0.672805, -1.30652, 1.16467, -0.990604},          {-0.577185, 0.00200075, -0.703859, -0.303082, -1.68814, -0.868155, 0.363235, 0.0214119, -0.645854, 0.764928, -0.514781, 0.7244, 0.465283, 0.189743, -1.39597, 0.213336, 0.446798, -1.26993, 0.174424, 0.424537, -1.15452, -1.75298, -0.309623, 0.128094, -0.689004, 2.0809, -0.371838, -0.186257, -0.631111, 0.565639, -0.299158, -1.02541, 0.383628, 0.889972, 1.29311, 0.123311, 0.791039, 0.696771, 0.155683, -0.237405, -0.267531, -1.70534, 0.492488, 1.29747, -0.0539445, 1.00713, -0.830485, 0.0360571, 0.774798, 0.102306, -0.189937, -0.367476, 0.141629, -0.549313, -0.622006, -1.32489, -1.15309, 0.0101935, 0.167965, 0.413663, -1.57047, 0.501152, 2.51988, -0.986897, -0.186802, 1.10116, 0.226443, -0.967959, -0.0998091, 0.7046, 0.809364, 0.172688, 2.23429, -0.339511, 1.30597, 0.963995, 0.494583, -1.05589, 0.413011, -0.141752, 1.92777, -0.864031, 0.429313, -0.183443, -0.217728, -0.0393808, -1.12099, 0.0921893, 0.0188809, 0.086726, 0.271202, 1.14053, 0.220355, 1.72112, -1.22066, -0.802663, 1.45791, 0.218067, -0.750516, 0.147931, 0.27226, -1.79245, -0.195111, 1.89608, 0.738197, 0.0166643, 1.77396, -2.07443, 0.223687, 0.0166528, -0.339643, -1.49554, 1.14263, 1.14484, -0.667709, -0.780103, -1.25457, 0.623897, -1.18715, 0.57305, 1.64423, 0.64025, 0.480327, -0.834055, -0.317288, -0.839789, 0.214061, -0.0402013, -1.04543, -0.560579, 1.55956, -0.809148, 0.523359, -0.150837, -0.702547, -0.216239, -1.09221, -2.07, -0.97618, -0.428155, -0.825335, 0.0663525, -0.252102, 1.42023, -0.211406, -0.549629, 0.288938, -0.367544, 0.981119, -0.861998, -0.0978796, -2.13574, 1.67448, -0.486979, -0.655064, 0.0876539, -0.920079, 0.838986, -0.385184, -0.768065, 0.0278169, 0.764948, -0.279529, -0.762522, 0.563328, -0.513939, -0.0184082, 0.895262, -0.857057, -0.219892, 0.309356, -0.485254, -0.106315, 0.601012, 0.5126, -0.45509, 1.07242, 0.745894, -0.662426, -1.51229, 0.0423359, 0.617365, 0.163451, -0.553203, -0.161091, -0.615686, -0.760901, -0.864786, -0.540975, 0.200036, 0.540387, 0.0481334, -0.75039, -0.254785, -0.333893, 0.161339, 0.734239, 0.391471, -0.476712, 0.598803},          {-0.823418, 0.380799, 0.441713, 0.428736, 2.65236, 0.905039, -0.25199, 0.0723711, 0.392547, 0.706137, 2.35118, 1.28268, -0.197731, 0.472847, 2.32248, 0.275431, 0.269705, 1.52667, -0.0931101, -0.987194, 1.41352, -0.848697, -0.569718, 2.11607, 0.295744, -0.262944, -0.712598, 1.6751, -0.531171, -1.00579, -0.201727, -0.786184, -0.296217, 0.543134, 0.601636, -0.394478, 0.619219, 1.0598, -0.463994, -0.868514, -0.185332, 1.70221, -1.77063, 0.424553, -0.540194, 1.01335, 0.67229, -0.078009, -0.975557, 0.0275916, 1.49203, 0.66986, -0.602254, -1.57721, 0.0540897, 0.180679, -0.73641, 0.858529, -0.228447, -0.674176, -0.823261, -0.0124315, 0.166844, 0.947693, 0.793836, -1.44588, 1.98137, 1.00171, 1.45505, 0.431462, -2.16347, 0.480645, -0.378093, 0.494897, -0.3219, -0.183139, -0.363703, -0.963229, -0.681948, 0.96694, -2.04823, 0.0700168, 0.650468, -0.404429, 0.375098, 0.053157, -1.37709, 0.202017, -0.0302393, 0.543329, 0.570758, 0.608443, -1.21033, -0.478777, 0.166424, 1.10919, -1.44998, 1.9565, -0.629106, -0.692402, 1.0042, 1.40405, 0.0770993, 1.39343, -0.869654, -0.944405, -0.529465, 0.561616, 0.948276, -0.381202, -0.0625773, 0.265479, 0.927656, 0.183621, 0.469049, -1.59988, 1.69697, 0.591354, 0.126989, -1.25269, 0.352193, 0.742284, -0.329177, -0.437253, -0.0491613, -0.544682, -0.358365, -0.292597, 0.741614, -1.51014, -0.273552, 0.681179, 1.05271, 0.516688, -0.342525, 1.18099, -2.05598, -0.545017, 0.100126, 0.856157, 0.439645, 0.435219, -0.163375, 0.569578, 0.203825, -0.204001, 0.402037, 0.380089, -0.965807, 0.736224, -1.56064, 0.887663, -1.94346, 0.390256, -0.14638, -0.528429, -1.30915, -1.83072, -1.05213, 0.432365, 0.611385, -1.27376, 0.436293, -0.426238, 0.371424, -0.122245, -0.892942, 0.784511, 0.87657, -0.843596, 0.821356, -0.723744, -0.188603, -0.770648, 0.216358, 0.147172, 0.608664, -0.344758, -0.0988283, 0.134224, 0.0870816, -0.782166, -0.519631, -1.6077, -0.229582, 0.664242, 0.645405, -0.269772, -0.539242, 0.218015, 1.09658, 1.1972, -0.272101, 0.809838, -0.497889, -0.672209, -1.75552, -1.43563, 1.19184, 0.681575},          {-0.598903, -0.550104, -0.52355, -0.188229, 0.757833, 0.122506, 1.44765, -1.51711, -0.299931, -0.968524, -0.749438, -0.157857, 1.04299, -0.164433, 0.860262, -0.357564, -0.922937, 1.0352, -0.341289, 0.173465, 1.40978, 0.806245, -0.0201346, 0.155425, 0.367049, -0.468195, 0.26194, -0.237561, -0.514518, -0.105776, 0.420625, 0.909893, 1.06559, -0.357176, 0.638831, -0.549053, -0.415928, 1.08195, -0.0815873, -0.517886, 0.296801, -0.0327398, 0.824502, -0.525542, -0.56462, 0.360483, -1.28647, -0.636515, 0.768898, -0.402619, -0.181267, -1.17698, -0.675118, 0.20146, -0.605803, -0.392849, -0.411201, 0.1126, -0.452895, -1.14425, -0.0706288, -0.281412, -0.31817, -0.884616, -0.33598, 0.222194, -0.861537, -0.935402, 0.374003, 1.54709, -1.06125, 0.127386, -0.153661, 0.293125, -0.648531, 1.05186, 0.00292419, 1.11123, -0.760627, -2.05218, -0.165579, -0.359261, -0.287854, -1.38551, -0.192489, -0.0142184, -1.25271, -0.843711, -0.985648, -2.14909, -0.0186729, 0.493857, 0.775097, 0.0621715, 0.538066, -0.741633, 0.360059, -1.20396, 0.67766, -0.0761122, 0.645486, -0.153375, 0.930736, 0.45499, 0.763076, -0.136051, -0.770157, -0.806827, -0.441221, -0.546789, -0.976304, -0.129629, -0.912183, -0.00837599, -0.0856566, 0.0697607, 1.35127, -0.0672679, 0.0487817, 0.190426, 0.486384, -0.593641, -0.626597, 0.570286, 1.31472, 0.727246, -1.52312, 0.531825, 0.449111, 0.436264, -0.577608, 1.21207, -0.0324695, -0.658513, 0.0238966, -0.495386, 0.521196, -0.719584, 0.528344, 1.49786, -0.143551, -0.301187, -0.53113, 0.00854805, -0.219704, 0.245421, 0.0791451, -0.584985, 0.227921, -0.957152, -0.53843, -1.32728, -0.767072, -0.662043, 0.232316, -0.0224666, 0.745536, -1.20467, -0.212089, 0.951174, 1.31489, -0.152599, -0.0401533, 0.997693, -0.0702789, 0.110847, 0.623449, -1.20259, -0.229778, -0.708925, -0.0090411, 1.05347, -0.553273, -0.23238, -0.831694, -0.74302, -1.64773, 0.678227, 1.25874, -1.08337, -0.206111, -0.341693, -0.0548461, 0.021161, 0.492893, 1.81201, -0.632714, 1.22094, 0.511431, 0.139088, -1.1215, 0.814548, -0.4984, 0.724605, 1.36276, 0.740758, 1.1258, 0.687195, -0.80727, -0.210761},          {0.136472, 0.0676158, -0.840637, 2.00275, 0.310164, 0.703495, 0.0530234, 0.642718, -0.272215, -0.698208, -0.724258, -0.795768, 0.0919211, -0.809739, 1.05545, 1.01084, 0.0934803, -0.39034, 1.19008, 0.204798, -0.312871, -0.89373, 0.372958, 1.37577, -0.111703, 1.42117, 0.111701, -0.251531, -0.636292, 1.43268, -0.238121, 1.67919, -0.265951, 0.414543, -1.13401, 0.480393, -2.05768, -0.0825599, -0.228999, -0.178089, 0.628501, 0.997306, 0.306325, -0.737603, -0.329901, 0.927823, 0.0195058, 0.456329, 2.0744, 0.942688, -0.0017025, 0.741748, 0.751472, -0.301618, -0.054383, 0.768873, 2.09881, -0.349266, -0.532971, -0.507109, -0.683053, -0.458929, -0.610649, -0.499344, -0.563861, 1.32329, -0.541804, 1.81619, 0.421569, -0.110533, 0.173826, -1.2713, -0.248694, -0.353467, 1.28057, -1.89039, 0.0628244, 1.06295, 0.476042, -0.186707, 0.121963, 0.786043, 0.00588527, 0.491155, -0.443082, 0.0581695, 0.333261, 0.498635, 0.0321047, -0.52187, 0.0203444, 0.384157, 0.907186, 0.759188, -0.743464, 0.801651, -0.386188, -0.716903, 0.336286, 1.86066, -0.0452195, 0.535105, 0.152163, -0.397392, -1.01934, -0.440914, 1.39284, 0.618149, -0.361474, -1.34618, -0.0977204, 0.703735, 1.46512, -0.990949, 0.284948, -0.209649, 0.367366, 0.810345, -1.59966, -0.0882599, -0.309574, -0.158926, 1.3708, -1.20885, -1.71313, -1.06225, 0.68935, 0.304657, -0.0273226, 0.632294, -0.0936451, -0.76886, 1.47763, 0.385299, 0.471012, -1.30475, 0.148354, 1.31088, 0.697501, 0.328678, 0.485987, -0.226797, 1.55139, 0.168321, 0.529315, 0.509285, -0.382232, -0.965476, 1.30988, 0.146991, 0.526487, 1.4614, 0.876483, -0.0493464, -1.35586, 0.463778, -0.558769, 0.174925, 1.40458, -1.33121, 0.0203772, -0.615263, 0.467958, -0.361831, -1.03102, 1.79953, 0.634536, -0.0437456, -0.670317, 0.892622, -0.310001, -0.52676, 1.07314, -1.28013, 0.588799, -0.844059, 0.818576, -0.643092, 0.856823, 0.182973, 0.876918, 1.28605, 0.235656, 0.207455, -0.573538, -0.290554, 2.35392, -0.406035, 1.27002, 0.111846, -0.589686, 0.0954991, -0.562721, -0.427945, -0.31688, -1.00782, 0.0796161, 1.30002, -0.0054727, -0.331399},          {-0.809901, 0.0569591, -0.492214, -0.802176, -0.67174, -1.85251, -0.149186, -0.604944, 0.958413, 0.495526, -1.59882, -0.96047, 0.341518, -1.48144, -0.914552, -0.504466, -0.508587, -0.31523, 0.401154, -0.000257909, 0.855992, 0.247601, -1.05374, -0.484457, -0.997409, -0.234968, -0.683218, -0.890052, 0.130158, -0.390313, -0.233486, -0.449485, 0.229263, -0.13047, -0.913744, -0.389641, 1.43609, -0.0844235, -0.48974, 0.457275, 0.202622, -1.01636, -1.07737, -0.00506024, 0.260488, -0.062374, -0.422665, 0.166343, -0.417602, -0.561984, -0.525589, -0.404152, -0.175043, 0.579527, 1.9171, 0.46353, -1.27779, 0.498285, 0.942672, -0.699087, 0.564096, 0.388429, -1.31016, 0.823139, 0.0647525, -1.02034, -2.71481, -0.884012, -2.27181, -1.33846, 0.575995, -0.907516, -0.369825, 0.278956, -1.2406, -0.395051, 0.368301, 0.691069, -0.746027, -0.230036, -0.682997, -0.326476, 0.136648, -0.171453, 0.991118, -0.044616, -1.27587, 1.55318, 0.328649, 1.12438, -1.52436, -0.1066, -0.263798, -1.52143, -0.214258, -0.962471, 0.0534518, -0.633848, -1.34541, -1.29834, 0.877802, 0.503422, 0.907654, 0.562595, -0.844768, 1.65498, -2.27302, 0.00878335, -0.82218, 2.26561, -1.43774, -0.688249, -0.715462, 0.296556, -0.295884, 1.26701, 0.0528664, 0.631008, 1.28768, 0.303625, 0.679467, 0.426767, -1.49539, 0.533715, -0.912027, -0.329454, -0.333994, 0.505127, 1.09778, -0.520088, -0.153515, -0.662371, -1.23342, -0.542458, -0.121921, 1.02143, -0.261008, -0.918588, 1.47385, -1.14802, -0.70963, -0.273309, 1.36197, -1.57803, -0.298641, -1.26737, 0.522564, 0.819519, -1.94213, -1.24474, 0.763026, 1.79811, -0.255928, -0.441871, -1.35628, -0.0375556, 0.049629, -0.141569, 1.53467, 0.176309, -1.38526, 0.303159, 0.508887, 0.0132563, 0.925258, 0.100075, -0.218879, -0.720119, -0.101902, -0.13577, 1.73847, 1.39844, 0.0973974, 0.364443, -0.304954, 2.32384, 0.851702, 1.21847, -0.476916, 0.104079, -2.22563, 0.614057, -1.89411, -0.590563, 0.299338, -0.16394, -0.970441, -1.4343, -0.591618, 0.0314549, 0.97616, -1.15865, 0.598869, 0.643538, -1.22864, -0.635935, -0.887539, 0.480097, -0.390531, 0.464681},          {0.556977, -1.91918, -0.133978, -1.13368, 0.517309, -1.34561, -0.601899, -0.554714, -0.138805, -0.869225, -0.626074, -1.50575, -0.960188, 0.14965, 0.458502, -1.90492, 0.887959, 0.242981, -0.701652, -0.531657, -0.75281, 0.893896, -0.464351, -1.73633, -0.626516, -1.22222, -0.797585, -0.117463, 0.237913, 0.752908, -0.118893, -1.01523, 0.545527, -0.0673889, 0.264197, 0.21078, 1.979, -0.390557, 1.39546, -1.77115, -0.239506, 0.644214, 0.496313, 0.983665, 1.01098, 0.837308, -0.268252, 0.150553, -1.27665, 0.418294, 0.834484, 0.0765808, 0.740093, 0.658202, -0.723915, 0.421127, -1.91303, -0.485427, 0.238296, 0.869054, 1.39391, -1.48023, -0.241704, 0.132516, 0.508713, 0.360598, 1.76791, -0.224022, -0.215825, -0.623694, 0.414653, -1.24123, -1.50825, 1.14963, 1.00851, -0.339593, -0.129326, -1.3616, -0.153948, 0.381251, -0.689582, -0.018699, 0.065132, -0.0985039, -0.728613, -0.0119607, -0.00243543, 1.47538, -0.311773, -0.0320127, 1.89922, -1.64606, -1.58737, 1.18614, -0.277943, -1.0503, 0.371198, 1.04802, 1.04481, -1.79989, -1.67937, 0.279675, -0.936314, -1.48916, 0.569204, 0.820942, 1.28958, -0.104987, -0.0670011, 0.925491, 1.80079, 0.628888, -1.99493, 0.985972, -1.74251, -0.63889, 0.421421, 0.47508, -0.48704, -0.761577, -1.35395, -0.556659, 1.04058, 1.15504, 0.07308, 0.208226, 1.89169, 0.38174, -0.176511, 0.841196, -1.3791, -1.44921, -0.937534, 0.511366, 0.336981, 1.25253, 0.999645, 0.510472, 0.19874, 1.15297, 0.627525, 0.212395, -1.87288, -1.44533, -1.96709, -0.543088, -0.67488, 0.363721, 1.39207, -0.494536, 0.723111, 1.14041, -0.542509, 0.169748, 0.763965, 0.341389, 1.49063, 0.659432, -2.39621, -0.508731, -1.10062, 1.09885, -0.199547, 0.142887, 0.749443, -0.0950408, -0.181612, 0.651813, -0.310566, 1.2885, 0.622912, -0.927178, -0.208322, 1.07954, -0.19662, 0.00771559, 0.147359, 1.51327, -0.781276, 0.147958, 0.579119, -0.241808, 0.0331761, 0.151339, 0.0397303, -0.947662, -1.34192, -0.62616, 0.0720814, -0.669598, -0.684889, 1.36728, 0.599631, -0.271235, -0.582245, 0.188591, -1.21257, -0.929924, 0.629918, -1.02826}};

double bias3[10] = {-0.0972961, 0.0300511, -0.0173903, -0.00445253, 0.0983954, -0.211495, -0.157007, 0.113646, 0.259432, -0.0774153};  

int main(void) {}

//1 / (1 + Math.exp(-out2[i]) ); 
double sigmoid(double val) {
        return 1 /  (1 + std::exp(-val) );
}


double softmax(double arr[], int size) {

        double nominators[size];
        double  denominator = 0.0;
        double output = 0.0;

        for ( int i=0; i < size; i++ ) {
                nominators[i] =  std::exp(arr[i]);   //eleva a constante de euler a cada elemento do array
                denominator += nominators[i]; // o denominador é a soma de todos os elementos do numerador
        }

        for (int i=0; i < size; i++) {
                double res = nominators[i] / denominator;

                if (res > output) {
                        output = res;
                }
        }

        return output;
}


void neural_net(int ptr, int len) {

        uint8_t *img;
        img = (uint8_t *) ptr;

        double out2[200];

        for (int i=0; i < 200; i++) {
          out2[i] = bias2[i];

          for (int j=0; j< 784; j++) {
          
            out2[i] += img[j] * w12[i][j];
          
          }

          out2[i] = sigmoid(out2[i]); //sigmoid
        }


        double out3[10];

        for (int i=0; i<10; i++) {
          out3[i] = bias3[i];

          for (int j=0; j< 200; j++) {
            out3[i] += out2[j] * w23[i][j];
          }

        }

        double response = softmax(out3, 10);

        std::cout << "Number: " << response << std::endl;
}
clear all
close all

scan = [924;924;924;924;924;906;908;928;967;998;995;939;925;940;977;1023;998;928;889;928;996;1025;1026;1034;1041;1010;1005;995;993;993;968;952;959;950;925;906;940;988;991;952;924;924;933;961;951;920;927;968;985;985;921;885;912;948;982;966;935;937;938;917;891;883;914;976;1002;975;940;922;915;920;933;941;937;922;933;924;909;893;891;909;940;947;950;958;956;942;945;958;967;963;965;962;950;918;905;914;944;953;946;931;916;911;906;910;943;962;969;963;962;977;973;974;951;931;937;952;968;938;900;919;957;995;999;983;968;945;913;905;934;966;967;944;918;894;920;947;962;942;880;877;896;925;932;950;945;922;899;891;927;979;991;1012;1038;1040;1023;1002;984;962;937;931;930;941;945;951;935;920;916;954;1000;993;969;941;936;951;960;969;963;969;1007;1041;1036;973;944;940;942;947;939;953;961;966;950;929;920;931;942;942;908;873;876;932;998;1038;1032;1026;973;939;920;954;983;993;936;904;916;953;979;982;945;894;889;922;1019;1053;1019;969;931;925;957;995;1008;989;935;911;905;931;951;955;941;939;946;958;977;970;986;979;958;929;909;938;958;954;928;912;912;891;896;920;961;981;989;994;983;957;942;929;933;941;949;948;966;966;962;952;966;993;994;990;977;942;921;943;972;981;1001;1004;993;977;962;965;964;946;915;915;918;944;997;1015;993;964;935;926;937;954;986;1016;1020;1017;1007;990;967;933;906;899;913;922;958;988;989;995;992;1011;1030;1038;1029;1017;1000;986;988;991;989;959;940;914;916;916;923;931;936;932;941;955;955;944;925;908;916;932;951;970;975;952;940;937;940;940;925;903;895;921;955;975;984;969;954;957;958;970;963;933;915;911;923;945;1011;1014;1007;969;923;888;914;963;977;973;974;969;955;954;919;917;923;932;939;947;957;953;947;964;974;994;993;977;956;934;927;934;950;948;955;961;964;954;921;892;873;874;900;944;1038;1060;1016;970;931;932;928;934;945;947;944;917;876;840;850;895;934;935;916;901;904;924;959;994;1017;992;939;905;880;894;910;942;943;937;912;906;929;945;958;971;975;960;948;950;977;1011;1033;1057;1037;1010;967;934;923;927;958;985;993;1008;1011;1014;1020;1032;1034;1033;1014;990;951;936;958;982;1003;1017;1009;993;967;964;976;1000;1008;1022;1013;974;942;930;952;982;1020;1037;1030;1005;957;914;908;917;924;934;926;912;888;885;893;910;921;916;916;908;909;918;935;947;960;990;986;979;934;892;884;894;908;923;921;913;898;892;933;967;999;1002;980;974;960;957;972;987;988;996;981;971;950;923;927;944;967;980;970;948;923;918;940;970;983;988;972;964;949;958;970;970;975;969;975;974;977;966;950;938;939;951;972;993;1002;1006;995;966;954;938;934;939;950;976;960;949;931;918;938;947;950;946;938;922;911;904;914;925;930;931;936;927;918;920;927;912;928;940;974;995;997;1005;990;979;963;931;943;942;955;958;932;905;884;879;897;914;940;943;951;951;948;954;943;938;925;923;923;928;937;954;960;954;931;914;905;924;951;992;995;990;974;971;960;953;947;948;956;952;957;951;949;936;921;907;917;943;963;980;975;958;930;913;929;952;973;989;985;931;898;892;889;913;943;972;985;990;993;1009;1022;1046;1058;1059;1045;996;944;901;889;908;938;954;959;950;929;935;953;963;977;985;972;917;886;877;870;868;884;915;947;997;1024;1035;1038;1022;1001;978;966;956;959;969;979;974;969;962;955;941;924;922;935;939;943;953;967;981;991;984;979;962;940;928;932;932;956;957;947;944;940;936;941;952;951;966;972;967;966;967;972;962;951;954;953;960;963;983;993;985;978;972;957;964;953;967;977;988;1007;1028;1027;1016;968;932;889;858;851;866;875;876;871;859;848;860;876;914;948;1000;1025;986;948;887;860;851;868;908;956;996;1012;989;940;918;917;922;932;956;996;1010;1008;1004;971;933;917;927;936;991;1038;1066;1061;1021;988;947;929;925;957;977;1009;1004;994;975;960;944;941;942;964;975;988;987;975;937;922;927;947;974;982;976;969;931;912;913;925;938;951;961;950;927;911;900;917;928;953;966;998;1001;994;996;981;959;926;902;897;892;898;905;922;949;976;992;1002;997;980;982;965;960;967;988;996;1012;1021;1018;1009;979;945;920;885;874;868;863;873;918;918;927;924;908;900;906;921;934;954;963;948;921;913;903;906;898;887;891;904;910;946;954;963;968;950;936;910;894;888;900;912;935;965;971;978;972;954;958;949;946;937;944;950;972;975;968;966;964;968;964;966;973;991;1006;1009;1016;1006;990;963;946;921;932;963;993;1006;1010;1009;1002;972;964;955;949;950;956;963;973;983;993;1005;999;1000;984;969;954;919;909;909;911;920;923;941;960;963;966;970;963;953;958;971;969;978;968;958;950;944;942;940;941;920;918;913;914;937;960;992;1025;1028;1018;1001;941;912;891;878;869;874;879;897;921;937;931;916;913;906;907;909;910;892;885;877;861;855;854;864;887;902;906;919;929;910;894;864;845;827;827;849;907;944;967;980;976;942;933;912;904;903;919;947;952;946;938;920;912;917;927;937;960;970;956;955;936;923;917;926;937;945;948;976;999;1005;1013;1006;976;958;961;966;972;989;995;1021;1023;1017;1005;980;980;984;990;1001;994;960;914;865;833;834;878;912;979;1006;1013;1029;1035;1016;1006;992;993;972;967;963;934;913;913;919;953;979;989;988;970;941;934;928;937;944;960;979;983;974;968;955;943;928;933;937;953;961;960;978;962;957;942;935;925;920;925;937;960;972;967;961;953;934;932;929;922;907;906;908;911;920;918;937;934;958;969;982;999;987;958;955;935;935;945;966;996;1001;1009;1009;1010;1016;1009;1012;1010;1002;995;989;970;948;930;928;919;923;917;930;951;957;962;968;966;964;970;968;958;947;937;925;914;926;928;953;994;1001;996;982;963;951;948;952;963;964;987;996;1005;1005;1004;997;992;987;981;991;982;970;967;973;964;962;960;953;919;885;860;852;874;903;930;952;962;950;938;909;913;917;921;945;970;1002;1010;1019;1001;974;953;919;896;900;921;950;965;955;941;931;934;927;945;962;969;982;981;981;975;969;963;957;953;954;959;952;966;954;965;961;966;955;931;911;895;870;881;885;909;941;952;967;980;962;956;935;926;923;913;912;911;909;919;932;938;943;941;940;934;940;948;956;962;950;942;934;927;910;902;905;904;916;917;916;894;870;866;868;903;942;974;1016;1032;1047;1045;1045;1026;1014;1008;1006;983;980;975;963;942;916;913;900;900;896;902;897;914;942;965;987;1006;989;980;960;956;963;982;999;1018;1007;987;969;981;972;979;996;999;1006;1000;1000;961;936;913;892;890;918;940;959;996;1012;1007;997;986;954;940;938;937;951;960;967;985;976;971;963;967;972;975;988;1010;998;990;986;972;971;979;991;1000;1006;1006;997;984;971;964;969;983;1000;999;1002;978;953;939;927;907;921;930;946;968;969;973;983;966;946;931;921;925;923;925;934;935;943;946;949;954;955;943;935;932;943;944;965;970;950;938;919;879;851;848;847;866;887;905;925;922;899;886;874;893;912;924;969;1021;1031;1033;1007;977;939;918;906;918;934;954;970;1011;1036;1032;1014;988;956;946;923;926;929;948;960;1000;1025;1034;1041;1016;984;972;952;949;941;953;962;982;969;959;943;927;909;896;898;906;909;923;937;941;935;932;950;953;955;963;966;962;970;958;956;963;964;961;970;975;968;958;934;930;934;958;968;985;996;993;982;976;969;958;973;983;993;1009;1024;1036;1025;1012;989;948;915;913;898;910;918;912;900;888;869;860;858;870;890;903;928;947;956;966;979;987;1002;998;1006;1016;1012;1011;1006;1000;984;979;981;981;998;1007;1018;1027;1033;1046;1056;1061;1062;1052;1044;1031;1011;998;1002;1006;1004;988;963;926;895;891;903;929;968;995;1031;1048;1033;1001;982;959;957;950;959;968;971;966;970;962;950;932;925;920;914;918;922;952;960;970;982;990;986;985;985;982;984;990;1007;1017;1024;1009;1006;998;990;970;963;949;934;940;948;957;953;956;967;969;979;996;993;995;985;963;951;940;941;942;950;949;946;936;940;948;964;977;991;1005;998;1001;986;986;984;983;1004;1018;1013;1005;1003;996;981;976;982;991;983;987;983;971;957;931;928;917;910;926;927;948;956;965;953;944;933;935;927;934;920;920;921;912;914;918;934;976;999;1031;1038;1036;1028;1006;994;959;932;929;940;960;978;988;992;980;964;956;944;961;978;1017;1069;1096;1083;1055;1010;976;925;915;910;933;961;1018;1040;1036;1025;1006;993;970;961;975;1006;1031;1071;1104;1100;1080;1048;1010;980;958;947;953;977;990;1015;1012;1013;981;958;942;943;955;956;968;984;992;1011;1005;998;985;962;921;896;874;869;882;913;928;966;981;973;949;906;853;830;822;859;897;946;981;996;982;963;955;937;931;950;978;1004;1029;1041;1036;1030;1002;976;975;975;982;1009;1025;1045;1077;1093;1093;1084;1076;1062;1029;993;988;976;987;986;995;1006;1002;1011;1000;990;998;993;989;997;994;996;987;986;972;957;943;929;925;913;909;921;928;945;991;1015;1014;1009;989;969;971;964;977;999;1017;1036;1067;1072;1073;1051;1039;1022;1024;998;993;991;982;973;972;965;967;948;949;946;965;969;967;967;972;954;955;960;979;979;983;987;954;915;886;872;880;886;926;971;993;1010;1001;975;954;928;910;922;919;944;980;1013;1018;1038;1036;1019;1008;984;951;932;936;933;958;992;1003;1012;992;977;973;949;950;963;989;1014;1073;1085;1082;1054;1023;986;962;940;926;935;955;978;995;1003;999;989;984;987;996;993;991;984;989;986;1005;1035;1061;1065;1056;1051;1029;1010;996;997;995;1009;1008;1016;1023;1016;1010;1003;986;967;969;965;963;964;962;976;970;964;979;981;999;1010;1000;991;974;941;919;917;929;948;1000;1025;1036;1022;999;961;930;916;902;918;941;963;993;1009;1003;1000;982;979;973;983;1000;999;1007;1007;994;991;985;973;949;938;927;936;961;985;1012;1024;1039;1040;1022;996;969;945;948;940;941;958;972;979;969;962;956;939;938;953;964;985;1007;1017;1025;1028;1028;1036;1039;1038;1037;1016;1010;1002;1018;1042;1057;1079;1088;1068;1056;1025;987;968;964;963;970;980;998;993;983;966;956;952;936;954;955;987;1029;1050;1054;1050;1036;1046;1046;1040;1047;1023;1020;1011;1023;1038;1052;1058;1053;1041;1038;1007;984;988;998;1017;1043;1057;1052;1038;993;968;951;945;957;1003;1019;1031;1016;1000;986;958;922;924;942;950;995;1015;1024;1020;1006;987;964;951;952;968;975;1003;1028;1051;1071;1068;1059;1030;1018;990;981;983;984;997;987;986;984;984;984;982;986;987;1001;1012;1020;1016;1000;983;966;953;945;932;932;943;980;1020;1048;1075;1069;1042;1000;954;924;930;931;949;977;1002;1006;996;985;969;959;942;948;952;974;1008;1042;1030;1017;975;934;906;898;897;917;982;1000;1043;1090;1084;1072;1025;969;934;935;930;953;983;1001;1013;1001;977;957;937;924;938;945;970;976;1008;1058;1092;1114;1132;1128;1100;1039;993;966;942;940;988;1013;1041;1056;1051;1035;1003;957;931;927;930;954;979;992;1001;1009;1015;1028;1024;1026;1029;1016;1009;991;988;987;977;975;985;990;988;1001;1006;1014;1014;1008;1003;987;968;955;947;955;950;938;936;939;938;925;936;946;949;968;993;1015;1030;1050;1064;1069;1063;1037;1025;1015;1004;1027;1059;1067;1081;1084;1076;1050;1016;992;965;962;966;991;1024;1034;1043;1040;1032;1025;1008;1023;1027;1041;1040;1036;1028;1024;1015;1030;1042;1040;1045;1023;1009;1003;992;994;1004;1009;1018;1029;1059;1074;1084;1092;1088;1082;1060;1029;996;992;986;1003;1030;1044;1063;1077;1073;1068;1070;1063;1051;1064;1059;1052;1047;1038;1042;1024;1015;1005;1001;977;976;975;984;1021;1070;1093;1132;1155;1172;1151;1132;1098;1078;1073;1083;1099;1115;1132;1139;1121;1113;1105;1085;1063;1061;1074;1090;1118;1141;1146;1139;1123;1107;1087;1061;1046;1045;1052;1058;1087;1115;1121;1124;1116;1110;1108;1104;1115;1129;1136;1125;1129;1131;1125;1128;1117;1113;1110;1095;1100;1117;1128;1139;1155;1145;1134;1113;1080;1037;1028;1015;1037;1068;1087;1106;1112;1118;1119;1113;1106;1114;1118;1121;1127;1140;1147;1164;1184;1182;1175;1161;1132;1127;1125;1119;1128;1139;1142;1151;1162;1170;1174;1168;1139;1125;1114;1100;1094;1104;1143;1165;1187;1209;1220;1218;1207;1210;1212;1215;1216;1202;1192;1176;1142;1134;1132;1135;1172;1201;1221;1236;1248;1249;1243;1232;1203;1186;1184;1195;1200;1198;1202;1189;1167;1151;1115;1105;1091;1103;1137;1155;1191;1216;1224;1225;1198;1174;1173;1146;1133;1140;1143;1156;1158;1168;1163;1157;1132;1121;1104;1092;1074;1092;1118;1136;1155;1198;1198;1179;1151;1128;1101;1091;1086;1105;1120;1134;1174;1198;1206;1210;1189;1185;1175;1157;1160;1164;1170;1186;1190;1195;1204;1198;1198;1194;1186;1173;1177;1186;1189;1192;1185;1170;1164;1143;1135;1143;1159;1172;1182;1183;1187;1186;1188;1197;1203;1203;1215;1227;1249;1257;1261;1270;1291;1301;1319;1334;1338;1344;1334;1326;1326;1319;1319;1307;1296;1278;1254;1241;1250;1253;1249;1255;1275;1281;1290;1290;1292;1291;1289;1296;1307;1307;1318;1326;1322;1304;1299;1286;1286;1290;1306;1319;1338;1335;1327;1313;1299;1279;1278;1277;1291;1298;1305;1305;1301;1304;1295;1292;1289;1279;1266;1281;1281;1290;1294;1301;1307;1320;1319;1342;1356;1383;1388;1405;1417;1407;1412;1419;1418;1420;1427;1424;1431;1438;1462;1499;1546;1575;1607;1622;1609;1588;1552;1524;1485;1442;1426;1419;1432;1451;1481;1523;1542;1551;1547;1544;1546;1542;1533;1548;1560;1569;1611;1633;1645;1642;1628;1595;1560;1526;1517;1537;1614;1687;1738;1778;1792;1768;1733;1708;1687;1694;1721;1784;1827;1867;1896;1895;1874;1834;1807;1784;1768;1769;1790;1810;1835;1851;1850;1847;1832;1819;1792;1793;1795;1808;1827;1853;1880;1917;1942;1987;2052;2114;2170;2228;2295;2335;2412;2497;2556;2637;2670;2755;2820;2875;2914;2947;2988;3006;3010;3011;3001;2973;2932;2924;2910;2906;2908;2936;2956;2984;3011;3017;3020;3023;3037;3060;3090;3126;3180;3277;3399;3538;3629;3731;3906;4044;4149;4267;4461;4671;4848;5035;5353;5605;5840;6068;6233;6420;6617;6768;6977;7135;7296;7499;7695;7796;7829;7826;7811;7759;7719;7671;7626;7606;7594;7619;7643;7689;7789;7907;8116;8429;8727;9226;9687;10234;11085;12110;12984;13942;15736;16922;18600;20389;21809;23296;25896;28098;29802;31548;33917;36310;37513;39919;42304;44642;46897;49025;50534;52415;53732;54976;56504;57559;58808;59656;60831;61564;61990;62404;62607;62644;62575;62418;62081;61615;61172;60843;59869;58941;58166;57322;56114;54813;53788;52755;51342;50248;48776;47264;45751;44224;43073;41590;40123;39045;37973;36576;35233;33936;33304;32384;30900;29743;29174;28346;27008;25974;24997;24073;23402;22537;22121;21519;20599;20083;19582;19111;18395;17843;17427;17154;16487;15980;15620;15398;14858;14454;14150;13758;13390;13026;12852;12593;12186;11941;11703;11485;11127;10849;10648;10453;10131;9940;9749;9574;9349;9142;9043;8844;8623;8445;8324;8214;8077;7968;7895;7834;7757;7697;7607;7531;7472;7381;7321;7278;7217;7172;7136;7097;7025;6924;6903;6852;6790;6724;6690;6661;6611;6551;6508;6462;6407;6368;6350;6329;6311;6285;6244;6209;6118;6035;5980;5909;5869;5831;5786;5746;5704;5656;5606;5530;5457;5363;5301;5203;5101;5019;4961;4897;4851;4778;4701;4632;4509;4394;4373;4313;4235;4182;4117;4069;4004;3934;3884;3819;3737;3653;3630;3563;3495;3448;3394;3360;3343;3315;3299;3263;3229;3196;3169;3143;3108;3066;3032;2994;2952;2919;2913;2901;2876;2844;2814;2775;2664;2583;2559;2513;2488;2474;2464;2469;2470;2470;2458;2447;2403;2364;2364;2348;2348;2334;2326;2317;2282;2254;2241;2227;2203;2189;2177;2169;2160;2149;2125;2123;2087;2055;2026;2007;1989;1988;1984;1994;1998;1984;1956;1921;1869;1837;1816;1806;1806;1821;1824;1848;1850;1845;1842;1829;1804;1768;1739;1710;1701;1690;1703;1720;1721;1711;1692;1650;1586;1542;1523;1495;1493;1491;1498;1511;1530;1522;1514;1494;1436;1373;1342;1318;1323;1342;1346;1354;1350;1328;1311;1300;1303;1326;1337;1362;1410;1443;1453;1472;1479;1471;1452;1442;1431;1426;1434;1458;1480;1503;1504;1511;1486;1474;1476;1478;1473;1467;1462;1471;1494;1503;1512;1530;1539;1520;1500;1458;1438;1427;1430;1447;1493;1514;1524;1509;1472;1451;1442;1422;1422;1423;1432;1442;1457;1474;1474;1460;1442;1411;1403;1368;1344;1341;1363;1399;1470;1514;1505;1485;1401;1333;1300;1273;1289;1334;1377;1421;1458;1441;1410;1370;1315;1289;1291;1313;1384;1449;1463;1474;1472;1447;1408;1386;1356;1342;1350;1361;1394;1410;1413;1397;1366;1337;1319;1299;1309;1336;1368;1402;1428;1470;1506;1546;1564;1576;1567;1579;1612;1668;1714;1768;1825;1857;1868;1869;1866;1873;1865;1885;1886;1906;1915;1936;1970;1991;2010;2013;1977;1931;1887;1853;1817;1814;1816;1836;1872;1880;1866;1843;1775;1728;1717;1708;1719;1734;1739;1731;1717;1691;1660;1620;1584;1539;1498;1471;1447;1448;1474;1509;1564;1601;1581;1550;1495;1440;1405;1386;1371;1383;1390;1398;1371;1346;1317;1282;1262;1246;1249;1253;1270;1288;1321;1356;1355;1349;1334;1322;1301;1284;1265;1255;1264;1283;1308;1347;1363;1350;1322;1291;1243;1209;1210;1209;1236;1249;1256;1265;1255;1237;1218;1187;1168;1153;1154;1161;1186;1192;1195;1195;1189;1168;1150;1139;1135;1116;1116;1122;1132;1135;1132;1140;1143;1140;1132;1129;1123;1103;1088;1082;1080;1092;1092;1115;1137;1122;1124;1088;1073;1048;1039;1045;1080;1124;1170;1197;1199;1186;1166;1140;1114;1095;1087;1087;1099;1102;1098;1103;1093;1075;1060;1052;1042;1051;1065;1083;1100;1117;1139;1149;1154;1140;1131;1120;1114;1108;1103;1104;1098;1098;1099;1100;1117;1115;1108;1106;1083;1068;1059;1067;1075;1086;1101;1111;1128;1131;1129;1115;1085;1063;1044;1036;1039;1049;1065;1085;1106;1107;1102;1100;1099;1084;1080;1077;1074;1083;1097;1126;1156;1180;1179;1185;1166;1138;1105;1091;1071;1063;1072;1080;1096;1092;1083;1086;1063;1047;1035;1044;1057;1055;1072;1102;1124;1133;1132;1126;1114;1085;1032;1025;1031;1037;1069;1104;1145;1148;1134;1109;1061;1031;1011;1012;1036;1060;1086;1106;1138;1156;1157;1168;1167;1138;1118;1102;1072;1052;1039;1039;1047;1054;1040;1042;1041;1016;1010;1003;991;987;979;984;981;978;979;974;971;970;978;983;1016;1054;1069;1082;1081;1067;1045;1030;1036;1046;1048;1060;1059;1061;1061;1067;1065;1056;1040;1040;1034;1036;1038;1059;1065;1066;1061;1066;1073;1066;1060;1056;1047;1036;1013;995;985;974;974;978;1004;1036;1066;1074;1074;1058;1046;1026;1017;1011;1019;1033;1050;1051;1047;1039;1033;1006;994;976;973;966;976;986;1030;1063;1061;1059;1035;1009;974;953;947;957;971;989;1005;1003;1004;1003;995;990;978;987;985;1005;1012;1033;1048;1069;1071;1069;1059;1048;1035;1035;1037;1034;1040;1048;1049;1041;1033;1020;1005;996;984;980;966;956;930;911;909;904;916;934;975;994;1008;1006;1009;996;985;986;995;1011;1013;1023;1032;1018;1001;996;1008;1011;1020;1029;1031;1025;1018;1016;1008;1018;1020;1025;1038;1036;1040;1033;1019;1008;998;989;978;968;968;987;987;1005;996;997;996;983;976;979;977;974;982;986;990;984;990;1002;1011;1027;1029;1032;1027;1003;995;993;996;1003;1018;1016;1017;1003;990;977;971;968;955;963;962;963;968;966;971;955;939;961;989;1021;1043;1043;1043;1017;981;968;962;966;975;997;1005;997;997;989;994;988;996;996;1002;1006;1013;1023;1022;1014;1015;1005;1017;1018;1026;1028;1026;1019;1022;1033;1030;1020;1002;983;977;966;973;978;980;970;970;986;994;1012;1020;1029;1028;1020;1021;1021;1023;1009;988;970;966;952;959;973;980;1000;1016;1034;1045;1055;1057;1043;1028;1004;968;950;946;952;968;1006;1026;1048;1063;1050;1035;1013;990;997;1004;1018;1025;1026;1017;1001;974;968;966;992;1023;1055;1101;1112;1099;1052;1004;976;972;978;1009;1027;1053;1060;1055;1037;1005;986;972;980;990;1007;1029;1048;1065;1067;1059;1034;1012;999;1006;1012;1035;1048;1062;1084;1080;1059;1027;977;927;915;914;939;986;1048;1065;1081;1055;1009;1010;987;985;985;1005;1021;1043;1040;1017;988;966;970;982;987;1002;1011;1017;1024;1031;1010;992;957;922;915;914;935;970;1004;1021;1014;1009;1007;1011;1003;1022;1010;1008;989;976;971;978;976;971;980;989;1000;995;1006;1005;1001;1006;1009;1005;996;988;977;975;971;957;964;975;979;998;1018;1018;1019;1016;1016;1009;1003;997;999;1005;1000;997;1003;1011;1025;1032;1046;1049;1021;1014;999;985;984;990;990;986;988;988;1012;1025;1027;1010;990;975;962;961;993;1005;1020;1046;1058;1062;1046;1032;1018;1017;1022;1027;1036;1026;1000;984;966;954;952;953;963;972;994;1002;1019;1018;1013;994;992;995;995;1005;1025;1022;1014;1009;1008;996;981;952;933;913;910;924;944;988;1006;1026;1029;1021;1002;977;970;956;955;988;1002;1008;1005;990;983;979;973;975;969;960;948;934;917;919;907;905;892;890;883;887;907;932;958;986;1007;1007;990;945;908;879;851;857;886;912;959;1003;1025;1017;1005;964;947;913;923;934;949;964;964;957;945;931;930;938;960;972;971;958;921;918;890;875;894;923;970;1008;1027;1019;1006;996;985;964;955;959;986;1002;1014;1015;1016;1015;1008;1006;1001;987;997;1024;1036;1030;1010;957;931;916;918;965;1010;1040;1057;1014;960;910;882;867;886;925;959;1004;1015;1017;980;965;975;981;1003;1041;1054;1057;1054;1036;1012;986;958;934;941;961;990;1032;1046;1037;1013;979;948;939;928;948;971;1000;1011;1022;1007;992;977;936;951;953;960;1001;1014;1010;977;939;904;897;895;934;966;985;1001;1012;1000;991;963;929;918;930;956;990;999;989;950;920;907;902;910;930;962;968;963;947;931;905;877;881;908;923;948;996;1011;1014;992;930;903;891;902;933;959;964;975;973;974;971;968;967;977;999;1002;994;955;929;896;875;890;916;964;1022;1043;1022;999;969;951;953;972;987;993;985;971;954;972;992;1036;1058;1067;1030;991;938;908;902;914;937;971;980;973;968;970;977;971;969;966;962;951;945;937;920;911;917;960;964;989;1001;995;995;991;981;967;955;934;941;938;947;943;957;954;959;965;973;995;1004;1010;1008;989;954;923;926;939;957;971;975;976;962;957;942;926;925;913;916;914;896;883;882;910;939;961;975;965;948;928;925;931;941;959;989;983;972;942;918;925;929;944;969;982;983;982;982;978;983;967;952;937;938;944;945;950;964;979;995;993;972;917;901;909;937;993;1039;1045;1022;977;950;949;979;1027;1061;1064;1041;1009;976;960;959;975;1013;1037;1026;1015;978;947;942;936;964;990;1000;998;979;948;932;917;925;955;971;994;1005;1001;977;958;963;973;996;1002;1006;986;969;955;950;961;974;996;1016;1004;990;970;937;945;946;966;1015;1023;1021;985;946;914;893;887;885;862;845;837;847;877;893;944;995;1035;1024;995;959;932;916;908;933;971;1004;1024;1018;999;998;991;1017;1030;1045;1039;1013;984;957;955;980;997;998;980;939;917;902;893;908;932;958;978;988;997;1004;1010;1033;1032;1005;950;915;926;937;976;1020;1014;1007;978;951;947;953;986;1037;1048;1031;981;949;936;937;954;963;951;924;900;900;915;935;964;980;995;988;961;924;911;916;937;977;1006;997;972;928;922;945;988;1004;1021;996;970;960;960;964;944;951;966;985;987;982;955;895;857;863;909;946;951;930;898;885;880;914;941;966;986;927;843;827;828;930;993;991;964;896;867;893;950;991;994;971;941;947;939;934;951;1005;1029;1009;982;957;945;951;951;972;968;940;907;895;902;935;958;1002;1017;1017;994;967;945;955;973;986;981;948;918;901;892;911;939;979;975;953;945;958;984;996;993;952;920;911;910;918;919;920;944;967;995;1024;1037;1014;976;941;920;913;922;946;967;971;955;933;916;924;934;965;988;984;949;915;918;943;969;977;964;947;941;940;960;1002;1018;999;964;943;970;995;1020;1025;997;978;979;986;1015;1032;991;946;901;901;942;998;992;950;916;925;961;1007;1031;1015;977;959;956;990;994;976;981;982;980;961;963;1001;1013;986;961;936;944;982;1015;1032;1020;939;889;900;941;953;944;959;973;968;954;956;967;959;949;946;980;1024;1029;981;946;918;916;930;969;952;923;949;991;1023;1029;1004;979;991;1032;1030;972;912;907;973;1029;1025;980;921;938;984;1037;1018;955;933;1001;1019;1007;929;883;913;955;967;938;904;936;1021;1039;985;922;909;977;1005;958;860;859;888;947;968;972;978;1000;997;986;959;929;935;947;938;921;903;907;916;911;893;902;963;1022;1034;982;910;884;941;1000;1004;946;942;986;995;962;935;964;1005;1000;951;905;907;933;940;935;935;951;994;988;948;903;960;955;905;866;884;921;919;904;917;917;905;936;974;980;970;992;992;992;992];

% output file where to save the data
path = "../TF_Output/Test.csv";

cycles = 500;
T = 0.01;
t=0:0.000001:(cycles*T);
A=zeros(1,length(t));
B=zeros(1,length(t));
Z=zeros(1,length(t));
D=zeros(1,length(t));
signal=zeros(1,length(t));

offset = 2.5;

pos = 2700 * sin(2*pi*t/T);

plot(t, pos);

encoder_pos = 0;
cycle_counter = 0;
cycle_counter_flag = 0;
cycle_counter_bit = 0;
for i = 2:length(t)
  if round(pos(i)) > encoder_pos
    if round(pos(i)) > encoder_pos+1
      if A(i-1) == 0 && B(i-1) == 0
        A(i) = 1;
        B(i) = 1;
        encoder_pos = encoder_pos + 2;
      elseif A(i-1) == 0 && B(i-1) == 1
        A(i) = 0;
        B(i) = 0;
        encoder_pos = encoder_pos + 1;
      elseif A(i-1) == 1 && B(i-1) == 0
        A(i) = 1;
        B(i) = 1;
        encoder_pos = encoder_pos + 1;
      elseif A(i-1) == 1 && B(i-1) == 1
        A(i) = 0;
        B(i) = 0;
        encoder_pos = encoder_pos + 2;
      end
    else
      if A(i-1) == 0 && B(i-1) == 0
        A(i) = 1;
        B(i) = 0;
      elseif A(i-1) == 0 && B(i-1) == 1
        A(i) = 0;
        B(i) = 0;
      elseif A(i-1) == 1 && B(i-1) == 0
        A(i) = 1;
        B(i) = 1;
      elseif A(i-1) == 1 && B(i-1) == 1
        A(i) = 0;
        B(i) = 1;
      end
      encoder_pos = encoder_pos + 1;
    end
  elseif round(pos(i)) < encoder_pos
    if round(pos(i)) < encoder_pos-1
      if A(i-1) == 0 && B(i-1) == 0
        A(i) = 0;
        B(i) = 1;
        encoder_pos = encoder_pos - 1;
      elseif A(i-1) == 0 && B(i-1) == 1
        A(i) = 1;
        B(i) = 0;
        encoder_pos = encoder_pos - 2;
      elseif A(i-1) == 1 && B(i-1) == 0
        A(i) = 0;
        B(i) = 1;
        encoder_pos = encoder_pos - 2;
      elseif A(i-1) == 1 && B(i-1) == 1
        A(i) = 1;
        B(i) = 0;
        encoder_pos = encoder_pos - 1;
      end
    else
      if A(i-1) == 0 && B(i-1) == 0
        A(i) = 0;
        B(i) = 1;
      elseif A(i-1) == 0 && B(i-1) == 1
        A(i) = 1;
        B(i) = 1;
      elseif A(i-1) == 1 && B(i-1) == 0
        A(i) = 0;
        B(i) = 0;
      elseif A(i-1) == 1 && B(i-1) == 1
        A(i) = 1;
        B(i) = 0;
      end
      encoder_pos = encoder_pos - 1;
    end
  else
    A(i) = A(i-1);
    B(i) = B(i-1);
  end
  if encoder_pos >= -2500 && encoder_pos < 2500
    signal(i) = scan(-encoder_pos+2500);
  else
    if i == 1
      signal(i) = 0;
    else
      signal(i) = signal(i-1);
    end
  end
  %if encoder_pos >= -2495 && encoder_pos < -2300
  %  signal(i) = signal(i) + 1.0;
  %end
  %if encoder_pos < 2495 && encoder_pos >= 2300
  %  signal(i) = signal(i) + 0.5;
  %end
  %signal(i) = 2.5 + 0.7*(encoder_pos+2700)/5400;
  if encoder_pos == 0
    if cycle_counter_flag == 0
      cycle_counter_flag = 1;
      cycle_counter = cycle_counter + 1;
      if cycle_counter == 20
        cycle_counter = 0;
        if cycle_counter_bit == 0
          cycle_counter_bit = 1;
        else
          cycle_counter_bit = 0;
        end
      end
    end
  else
    cycle_counter_flag = 0;
  end
  D(i) = cycle_counter_bit;
end

%V_AMP = Voltage going in to the amplifier (differential):
%1) Normalise to 16 bit resolution
%2) Account for 2.5V ADC input range (PGA=0)
V_AMP = signal ./ (2^16) .* 2.5;

%V_TP14 = Voltage at TP14:
%1) Inverse the signal
%2) Account for gain of IC9 amplifier (3.3/2)
V_TP14 = 3.3 - V_AMP .* 2 ./ 3.3;

[A_rec, B_rec] = reconstruct_encoder(A, B);

[position, direction] = decode_encoder(A_rec, B_rec);
Z_rec = zeros(1,length(A_rec));
Z_pos = [-4000, -2000, 0, 2000, 4000];
for i=2:length(A_rec)
  for j=Z_pos
    if position(i) >= j && position(i-1) < j
      Z_rec(i) = 1;
    end
  end
end
A_rec = [zeros(1,10000), 1, zeros(1,10000), A_rec];  
B_rec = [zeros(1,10000), 1, zeros(1,10000), B_rec];
Z_rec = [zeros(1,10000), 1, zeros(1,10000), Z_rec];

save_as_mat_file(A_rec, B_rec, Z_rec, 1/2000000)

[position] = sample_down(position, 2);
[direction] = sample_down(direction, 2);

visualise_data(position, direction, Z, V_TP14, D)

plot(pos)
plot(D*2500)
S = signal;
TF = create_TF();
F = 1000000;

%%%%%%%%%%%%%%%%%%% Only when running in conjunction with Octave
%path = "for_conversion.csv";
%[filepath,~,~] = fileparts(path);
%if ~exist(filepath, 'dir')
%  mkdir(filepath)
%end
%fp = fopen(path, "w");
%fprintf(fp, "signal\n");
%for i=1:length(A)
%  fprintf(fp, "%.5f\n", V_TP14(i));
%end
%fclose(fp);
%%%%%%%%%%%%%%%%%%% Only when running in conjunction with Octave
V_PDC = apply_TF(TF, F, V_TP14);

%V_PDC = dlmread("converted.csv", ",", 1, 0);
V_PDC = V_PDC + ones(1,length(V_PDC)).*offset;
visualise_data(position, direction, Z, V_PDC, D)

save_data(path, A, B, Z, V_PDC, D, F);

#include <include/socket.h>
#include <math.h>
#include <include/util.h>
#include <include/systems/chem.h>

struct element_struct {
    char * name;
    unsigned number;
    char * symbol;
};

struct element_struct2 {
    element_id element;
    double boiling_point;
    double electron_affinity;
    double electronegativity;
    double ionization_energy;
    double melting_point;
    double molar_mass;
};

struct chemdb_struct {
    char * name;
    char * description;
    element_data2 * data;
};

const element_id ELEMENT_COUNT = 119;
const chemdb_id CHEMDB_COUNT = 5;

const element_data elements[] = {
    { .name = "Nonexistium", .number = 0, .symbol = "-" },
    { .name = "Hydrogen", .number = 1, .symbol = "H" },
    { .name = "Helium", .number = 2, .symbol = "He" },
    { .name = "Lithium", .number = 3, .symbol = "Li" },
    { .name = "Beryllium", .number = 4, .symbol = "Be" },
    { .name = "Boron", .number = 5, .symbol = "B" },
    { .name = "Carbon", .number = 6, .symbol = "C" },
    { .name = "Nitrogen", .number = 7, .symbol = "N" },
    { .name = "Oxygen", .number = 8, .symbol = "O" },
    { .name = "Fluorine", .number = 9, .symbol = "F" },
    { .name = "Neon", .number = 10, .symbol = "Ne" },
    { .name = "Sodium", .number = 11, .symbol = "Na" },
    { .name = "Magnesium", .number = 12, .symbol = "Mg" },
    { .name = "Aluminum", .number = 13, .symbol = "Al" },
    { .name = "Silicon", .number = 14, .symbol = "Si" },
    { .name = "Phosphorus", .number = 15, .symbol = "P" },
    { .name = "Sulfur", .number = 16, .symbol = "S" },
    { .name = "Chlorine", .number = 17, .symbol = "Cl" },
    { .name = "Argon", .number = 18, .symbol = "Ar" },
    { .name = "Potassium", .number = 19, .symbol = "K" },
    { .name = "Calcium", .number = 20, .symbol = "Ca" },
    { .name = "Scandium", .number = 21, .symbol = "Sc" },
    { .name = "Titanium", .number = 22, .symbol = "Ti" },
    { .name = "Vanadium", .number = 23, .symbol = "V" },
    { .name = "Chromium", .number = 24, .symbol = "Cr" },
    { .name = "Manganese", .number = 25, .symbol = "Mn" },
    { .name = "Iron", .number = 26, .symbol = "Fe" },
    { .name = "Cobalt", .number = 27, .symbol = "Co" },
    { .name = "Nickel", .number = 28, .symbol = "Ni" },
    { .name = "Copper", .number = 29, .symbol = "Cu" },
    { .name = "Zinc", .number = 30, .symbol = "Zn" },
    { .name = "Gallium", .number = 31, .symbol = "Ga" },
    { .name = "Germanium", .number = 32, .symbol = "Ge" },
    { .name = "Arsenic", .number = 33, .symbol = "As" },
    { .name = "Selenium", .number = 34, .symbol = "Se" },
    { .name = "Bromine", .number = 35, .symbol = "Br" },
    { .name = "Krypton", .number = 36, .symbol = "Kr" },
    { .name = "Rubidium", .number = 37, .symbol = "Rb" },
    { .name = "Strontium", .number = 38, .symbol = "Sr" },
    { .name = "Yttrium", .number = 39, .symbol = "Y" },
    { .name = "Zirconium", .number = 40, .symbol = "Zr" },
    { .name = "Niobium", .number = 41, .symbol = "Nb" },
    { .name = "Molybdenum", .number = 42, .symbol = "Mo" },
    { .name = "Technetium", .number = 43, .symbol = "Tc" },
    { .name = "Ruthenium", .number = 44, .symbol = "Ru" },
    { .name = "Rhodium", .number = 45, .symbol = "Rh" },
    { .name = "Palladium", .number = 46, .symbol = "Pd" },
    { .name = "Silver", .number = 47, .symbol = "Ag" },
    { .name = "Cadmium", .number = 48, .symbol = "Cd" },
    { .name = "Indium", .number = 49, .symbol = "In" },
    { .name = "Tin", .number = 50, .symbol = "Sn" },
    { .name = "Antimony", .number = 51, .symbol = "Sb" },
    { .name = "Tellurium", .number = 52, .symbol = "Te" },
    { .name = "Iodine", .number = 53, .symbol = "I" },
    { .name = "Xenon", .number = 54, .symbol = "Xe" },
    { .name = "Cesium", .number = 55, .symbol = "Cs" },
    { .name = "Barium", .number = 56, .symbol = "Ba" },
    { .name = "Lanthanum", .number = 57, .symbol = "La" },
    { .name = "Cerium", .number = 58, .symbol = "Ce" },
    { .name = "Praseodymium", .number = 59, .symbol = "Pr" },
    { .name = "Neodymium", .number = 60, .symbol = "Nd" },
    { .name = "Promethium", .number = 61, .symbol = "Pm" },
    { .name = "Samarium", .number = 62, .symbol = "Sm" },
    { .name = "Europium", .number = 63, .symbol = "Eu" },
    { .name = "Gadolinium", .number = 64, .symbol = "Gd" },
    { .name = "Terbium", .number = 65, .symbol = "Tb" },
    { .name = "Dysprosium", .number = 66, .symbol = "Dy" },
    { .name = "Holmium", .number = 67, .symbol = "Ho" },
    { .name = "Erbium", .number = 68, .symbol = "Er" },
    { .name = "Thulium", .number = 69, .symbol = "Tm" },
    { .name = "Ytterbium", .number = 70, .symbol = "Yb" },
    { .name = "Lutetium", .number = 71, .symbol = "Lu" },
    { .name = "Hafnium", .number = 72, .symbol = "Hf" },
    { .name = "Tantalum", .number = 73, .symbol = "Ta" },
    { .name = "Tungsten", .number = 74, .symbol = "W" },
    { .name = "Rhenium", .number = 75, .symbol = "Re" },
    { .name = "Osmium", .number = 76, .symbol = "Os" },
    { .name = "Iridium", .number = 77, .symbol = "Ir" },
    { .name = "Platinum", .number = 78, .symbol = "Pt" },
    { .name = "Gold", .number = 79, .symbol = "Au" },
    { .name = "Mercury", .number = 80, .symbol = "Hg" },
    { .name = "Thallium", .number = 81, .symbol = "Tl" },
    { .name = "Lead", .number = 82, .symbol = "Pb" },
    { .name = "Bismuth", .number = 83, .symbol = "Bi" },
    { .name = "Polonium", .number = 84, .symbol = "Po" },
    { .name = "Astatine", .number = 85, .symbol = "At" },
    { .name = "Radon", .number = 86, .symbol = "Rn" },
    { .name = "Francium", .number = 87, .symbol = "Fr" },
    { .name = "Radium", .number = 88, .symbol = "Ra" },
    { .name = "Actinium", .number = 89, .symbol = "Ac" },
    { .name = "Thorium", .number = 90, .symbol = "Th" },
    { .name = "Protactinium", .number = 91, .symbol = "Pa" },
    { .name = "Uranium", .number = 92, .symbol = "U" },
    { .name = "Neptunium", .number = 93, .symbol = "Np" },
    { .name = "Plutonium", .number = 94, .symbol = "Pu" },
    { .name = "Americium", .number = 95, .symbol = "Am" },
    { .name = "Curium", .number = 96, .symbol = "Cm" },
    { .name = "Berkelium", .number = 97, .symbol = "Bk" },
    { .name = "Californium", .number = 98, .symbol = "Cf" },
    { .name = "Einsteinium", .number = 99, .symbol = "Es" },
    { .name = "Fermium", .number = 100, .symbol = "Fm" },
    { .name = "Mendelevium", .number = 101, .symbol = "Md" },
    { .name = "Nobelium", .number = 102, .symbol = "No" },
    { .name = "Lawrencium", .number = 103, .symbol = "Lr" },
    { .name = "Rutherfordium", .number = 104, .symbol = "Rf" },
    { .name = "Dubnium", .number = 105, .symbol = "Db" },
    { .name = "Seaborgium", .number = 106, .symbol = "Sg" },
    { .name = "Bohrium", .number = 107, .symbol = "Bh" },
    { .name = "Hassium", .number = 108, .symbol = "Hs" },
    { .name = "Meitnerium", .number = 109, .symbol = "Mt" },
    { .name = "Darmstadtium", .number = 110, .symbol = "Ds" },
    { .name = "Roentgenium", .number = 111, .symbol = "Rg" },
    { .name = "Copernicium", .number = 112, .symbol = "Cn" },
    { .name = "Nihonium", .number = 113, .symbol = "Nh" },
    { .name = "Flerovium", .number = 114, .symbol = "Fl" },
    { .name = "Moscovium", .number = 115, .symbol = "Mc" },
    { .name = "Livermorium", .number = 116, .symbol = "Lv" },
    { .name = "Tennessine", .number = 117, .symbol = "Ts" },
    {  .name = "Oganesson", .number = 118, .symbol = "Og" }
};

element_data2 ptable_db[] = {
    { .element = 0, .molar_mass = NaN, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 1, .molar_mass = 1.008, .electronegativity = 2.2, .boiling_point = 20.28, .melting_point = 14.01, .ionization_energy = 1312.0, .electron_affinity = 72.8, },
    { .element = 2, .molar_mass = 4.0026, .electronegativity = NaN, .boiling_point = 4.22, .melting_point = NaN, .ionization_energy = 2372.3, .electron_affinity = 0.0, },
    { .element = 3, .molar_mass = 6.94, .electronegativity = 0.98, .boiling_point = 1615.0, .melting_point = 453.69, .ionization_energy = 520.2, .electron_affinity = 59.6, },
    { .element = 4, .molar_mass = 9.0122, .electronegativity = 1.57, .boiling_point = 2743.0, .melting_point = 1560.0, .ionization_energy = 899.5, .electron_affinity = 0.0, },
    { .element = 5, .molar_mass = 10.81, .electronegativity = 2.04, .boiling_point = 4273.0, .melting_point = 2348.0, .ionization_energy = 800.6, .electron_affinity = 26.7, },
    { .element = 6, .molar_mass = 12.011, .electronegativity = 2.55, .boiling_point = 4300.0, .melting_point = 3823.0, .ionization_energy = 1086.5, .electron_affinity = 153.9, },
    { .element = 7, .molar_mass = 14.007, .electronegativity = 3.04, .boiling_point = 77.36, .melting_point = 63.05, .ionization_energy = 1402.3, .electron_affinity = 7.0, },
    { .element = 8, .molar_mass = 15.999, .electronegativity = 3.44, .boiling_point = 90.2, .melting_point = 54.8, .ionization_energy = 1313.9, .electron_affinity = 141.0, },
    { .element = 9, .molar_mass = 18.998, .electronegativity = 3.98, .boiling_point = 85.03, .melting_point = 53.5, .ionization_energy = 1681.0, .electron_affinity = 328.0, },
    { .element = 10, .molar_mass = 20.18, .electronegativity = NaN, .boiling_point = 27.07, .melting_point = 24.56, .ionization_energy = 2080.7, .electron_affinity = 0.0, },
    { .element = 11, .molar_mass = 22.99, .electronegativity = 0.93, .boiling_point = 1156.0, .melting_point = 370.87, .ionization_energy = 495.8, .electron_affinity = 52.8, },
    { .element = 12, .molar_mass = 24.305, .electronegativity = 1.31, .boiling_point = 1363.0, .melting_point = 923.0, .ionization_energy = 737.7, .electron_affinity = 0.0, },
    { .element = 13, .molar_mass = 26.982, .electronegativity = 1.61, .boiling_point = 2792.0, .melting_point = 933.47, .ionization_energy = 577.5, .electron_affinity = 42.5, },
    { .element = 14, .molar_mass = 28.085, .electronegativity = 1.9, .boiling_point = 3173.0, .melting_point = 1687.0, .ionization_energy = 786.5, .electron_affinity = 133.6, },
    { .element = 15, .molar_mass = 30.974, .electronegativity = 2.19, .boiling_point = 553.6, .melting_point = 317.3, .ionization_energy = 1011.8, .electron_affinity = 72.0, },
    { .element = 16, .molar_mass = 32.06, .electronegativity = 2.58, .boiling_point = 717.87, .melting_point = 388.36, .ionization_energy = 999.6, .electron_affinity = 200.0, },
    { .element = 17, .molar_mass = 35.45, .electronegativity = 3.16, .boiling_point = 239.11, .melting_point = 171.6, .ionization_energy = 1251.2, .electron_affinity = 349.0, },
    { .element = 18, .molar_mass = 39.948, .electronegativity = NaN, .boiling_point = 87.3, .melting_point = 83.8, .ionization_energy = 1520.6, .electron_affinity = 0.0, },
    { .element = 19, .molar_mass = 39.098, .electronegativity = 0.82, .boiling_point = 1032.0, .melting_point = 336.53, .ionization_energy = 418.8, .electron_affinity = 48.4, },
    { .element = 20, .molar_mass = 40.078, .electronegativity = 1.0, .boiling_point = 1757.0, .melting_point = 1115.0, .ionization_energy = 589.8, .electron_affinity = 2.37, },
    { .element = 21, .molar_mass = 44.956, .electronegativity = 1.36, .boiling_point = 3103.0, .melting_point = 1814.0, .ionization_energy = 633.1, .electron_affinity = 18.1, },
    { .element = 22, .molar_mass = 47.867, .electronegativity = 1.54, .boiling_point = 3560.0, .melting_point = 1941.0, .ionization_energy = 658.8, .electron_affinity = 7.6, },
    { .element = 23, .molar_mass = 50.942, .electronegativity = 1.63, .boiling_point = 3680.0, .melting_point = 2183.0, .ionization_energy = 650.9, .electron_affinity = 50.6, },
    { .element = 24, .molar_mass = 51.996, .electronegativity = 1.66, .boiling_point = 2944.0, .melting_point = 2180.0, .ionization_energy = 652.9, .electron_affinity = 64.3, },
    { .element = 25, .molar_mass = 54.938, .electronegativity = 1.55, .boiling_point = 2334.0, .melting_point = 1519.0, .ionization_energy = 717.3, .electron_affinity = 0.0, },
    { .element = 26, .molar_mass = 55.845, .electronegativity = 1.83, .boiling_point = 3134.0, .melting_point = 1811.0, .ionization_energy = 762.5, .electron_affinity = 15.7, },
    { .element = 27, .molar_mass = 58.933, .electronegativity = 1.88, .boiling_point = 3200.0, .melting_point = 1768.0, .ionization_energy = 760.4, .electron_affinity = 63.7, },
    { .element = 28, .molar_mass = 58.693, .electronegativity = 1.91, .boiling_point = 3186.0, .melting_point = 1728.0, .ionization_energy = 737.1, .electron_affinity = 112.0, },
    { .element = 29, .molar_mass = 63.546, .electronegativity = 1.9, .boiling_point = 3200.0, .melting_point = 1357.77, .ionization_energy = 745.5, .electron_affinity = 118.4, },
    { .element = 30, .molar_mass = 65.38, .electronegativity = 1.65, .boiling_point = 1180.0, .melting_point = 692.68, .ionization_energy = 906.4, .electron_affinity = 0.0, },
    { .element = 31, .molar_mass = 69.723, .electronegativity = 1.81, .boiling_point = 2477.0, .melting_point = 302.91, .ionization_energy = 578.8, .electron_affinity = 28.9, },
    { .element = 32, .molar_mass = 72.63, .electronegativity = 2.01, .boiling_point = 3093.0, .melting_point = 1211.4, .ionization_energy = 762.0, .electron_affinity = 119.0, },
    { .element = 33, .molar_mass = 74.922, .electronegativity = 2.18, .boiling_point = 887.0, .melting_point = 1090.0, .ionization_energy = 947.0, .electron_affinity = 78.0, },
    { .element = 34, .molar_mass = 78.971, .electronegativity = 2.55, .boiling_point = 958.0, .melting_point = 494.0, .ionization_energy = 941.0, .electron_affinity = 195.0, },
    { .element = 35, .molar_mass = 79.904, .electronegativity = 2.96, .boiling_point = 332.0, .melting_point = 265.8, .ionization_energy = 1139.9, .electron_affinity = 324.6, },
    { .element = 36, .molar_mass = 83.798, .electronegativity = 3.0, .boiling_point = 119.93, .melting_point = 115.79, .ionization_energy = 1350.8, .electron_affinity = 0.0, },
    { .element = 37, .molar_mass = 85.468, .electronegativity = 0.82, .boiling_point = 961.0, .melting_point = 312.46, .ionization_energy = 403.0, .electron_affinity = 46.9, },
    { .element = 38, .molar_mass = 87.62, .electronegativity = 0.95, .boiling_point = 1655.0, .melting_point = 1050.0, .ionization_energy = 549.5, .electron_affinity = 5.03, },
    { .element = 39, .molar_mass = 88.906, .electronegativity = 1.22, .boiling_point = 3618.0, .melting_point = 1799.0, .ionization_energy = 600.0, .electron_affinity = 29.6, },
    { .element = 40, .molar_mass = 91.224, .electronegativity = 1.33, .boiling_point = 4682.0, .melting_point = 2128.0, .ionization_energy = 640.1, .electron_affinity = 41.1, },
    { .element = 41, .molar_mass = 92.906, .electronegativity = 1.6, .boiling_point = 5017.0, .melting_point = 2750.0, .ionization_energy = 652.1, .electron_affinity = 86.1, },
    { .element = 42, .molar_mass = 95.95, .electronegativity = 2.16, .boiling_point = 4912.0, .melting_point = 2896.0, .ionization_energy = 684.3, .electron_affinity = 71.9, },
    { .element = 43, .molar_mass = 9.0, .electronegativity = 1.9, .boiling_point = 4538.0, .melting_point = 2430.0, .ionization_energy = 702.0, .electron_affinity = 53.0, },
    { .element = 44, .molar_mass = 101.07, .electronegativity = 2.2, .boiling_point = 4423.0, .melting_point = 2607.0, .ionization_energy = 710.2, .electron_affinity = 101.3, },
    { .element = 45, .molar_mass = 102.91, .electronegativity = 2.28, .boiling_point = 3968.0, .melting_point = 2237.0, .ionization_energy = 719.7, .electron_affinity = 109.7, },
    { .element = 46, .molar_mass = 106.42, .electronegativity = 2.2, .boiling_point = 3236.0, .melting_point = 1828.05, .ionization_energy = 804.4, .electron_affinity = 53.7, },
    { .element = 47, .molar_mass = 107.87, .electronegativity = 1.93, .boiling_point = 2435.0, .melting_point = 1234.93, .ionization_energy = 731.0, .electron_affinity = 125.6, },
    { .element = 48, .molar_mass = 112.41, .electronegativity = 1.69, .boiling_point = 1040.0, .melting_point = 594.22, .ionization_energy = 867.8, .electron_affinity = 0.0, },
    { .element = 49, .molar_mass = 114.82, .electronegativity = 1.78, .boiling_point = 2345.0, .melting_point = 429.75, .ionization_energy = 558.3, .electron_affinity = 28.9, },
    { .element = 50, .molar_mass = 118.71, .electronegativity = 1.96, .boiling_point = 2875.0, .melting_point = 505.08, .ionization_energy = 708.6, .electron_affinity = 107.3, },
    { .element = 51, .molar_mass = 121.76, .electronegativity = 2.05, .boiling_point = 1860.0, .melting_point = 903.78, .ionization_energy = 834.0, .electron_affinity = 103.2, },
    { .element = 52, .molar_mass = 127.6, .electronegativity = 2.1, .boiling_point = 1261.0, .melting_point = 722.66, .ionization_energy = 869.3, .electron_affinity = 190.2, },
    { .element = 53, .molar_mass = 126.9, .electronegativity = 2.66, .boiling_point = 457.4, .melting_point = 386.85, .ionization_energy = 1008.4, .electron_affinity = 295.2, },
    { .element = 54, .molar_mass = 131.29, .electronegativity = 2.6, .boiling_point = 165.1, .melting_point = 161.3, .ionization_energy = 1170.4, .electron_affinity = 0.0, },
    { .element = 55, .molar_mass = 132.91, .electronegativity = 0.79, .boiling_point = 944.0, .melting_point = 301.59, .ionization_energy = 375.7, .electron_affinity = 45.5, },
    { .element = 56, .molar_mass = 137.33, .electronegativity = 0.89, .boiling_point = 2143.0, .melting_point = 1000.0, .ionization_energy = 502.9, .electron_affinity = 13.95, },
    { .element = 57, .molar_mass = 138.91, .electronegativity = 1.1, .boiling_point = 3737.0, .melting_point = 1193.0, .ionization_energy = 538.1, .electron_affinity = 48.0, },
    { .element = 58, .molar_mass = 140.12, .electronegativity = 1.12, .boiling_point = 3633.0, .melting_point = 1071.0, .ionization_energy = 534.4, .electron_affinity = 50.0, },
    { .element = 59, .molar_mass = 140.91, .electronegativity = 1.13, .boiling_point = 3563.0, .melting_point = 1204.0, .ionization_energy = 527.0, .electron_affinity = 50.0, },
    { .element = 60, .molar_mass = 144.24, .electronegativity = 1.14, .boiling_point = 3373.0, .melting_point = 1294.0, .ionization_energy = 533.1, .electron_affinity = 50.0, },
    { .element = 61, .molar_mass = 145.0, .electronegativity = NaN, .boiling_point = 3273.0, .melting_point = 1373.0, .ionization_energy = 540.0, .electron_affinity = 50.0, },
    { .element = 62, .molar_mass = 150.36, .electronegativity = 1.17, .boiling_point = 2076.0, .melting_point = 1345.0, .ionization_energy = 544.5, .electron_affinity = 50.0, },
    { .element = 63, .molar_mass = 151.96, .electronegativity = NaN, .boiling_point = 1800.0, .melting_point = 1095.0, .ionization_energy = 547.1, .electron_affinity = 50.0, },
    { .element = 64, .molar_mass = 157.25, .electronegativity = 1.2, .boiling_point = 3523.0, .melting_point = 1586.0, .ionization_energy = 593.4, .electron_affinity = 50.0, },
    { .element = 65, .molar_mass = 158.93, .electronegativity = NaN, .boiling_point = 3503.0, .melting_point = 1629.0, .ionization_energy = 565.8, .electron_affinity = 50.0, },
    { .element = 66, .molar_mass = 162.5, .electronegativity = 1.22, .boiling_point = 2840.0, .melting_point = 1685.0, .ionization_energy = 573.0, .electron_affinity = 50.0, },
    { .element = 67, .molar_mass = 164.93, .electronegativity = 1.23, .boiling_point = 2973.0, .melting_point = 1747.0, .ionization_energy = 581.0, .electron_affinity = 50.0, },
    { .element = 68, .molar_mass = 167.26, .electronegativity = 1.24, .boiling_point = 3141.0, .melting_point = 1770.0, .ionization_energy = 589.3, .electron_affinity = 50.0, },
    { .element = 69, .molar_mass = 168.93, .electronegativity = 1.25, .boiling_point = 2223.0, .melting_point = 1818.0, .ionization_energy = 596.7, .electron_affinity = 50.0, },
    { .element = 70, .molar_mass = 173.05, .electronegativity = NaN, .boiling_point = 1469.0, .melting_point = 1092.0, .ionization_energy = 603.4, .electron_affinity = 50.0, },
    { .element = 71, .molar_mass = 174.97, .electronegativity = 1.27, .boiling_point = 3675.0, .melting_point = 1936.0, .ionization_energy = 523.5, .electron_affinity = 50.0, },
    { .element = 72, .molar_mass = 178.49, .electronegativity = 1.3, .boiling_point = 4876.0, .melting_point = 2506.0, .ionization_energy = 658.5, .electron_affinity = 0.0, },
    { .element = 73, .molar_mass = 180.95, .electronegativity = 1.5, .boiling_point = 5731.0, .melting_point = 3290.0, .ionization_energy = 761.0, .electron_affinity = 31.0, },
    { .element = 74, .molar_mass = 183.84, .electronegativity = 2.36, .boiling_point = 5828.0, .melting_point = 3695.0, .ionization_energy = 770.0, .electron_affinity = 78.6, },
    { .element = 75, .molar_mass = 186.21, .electronegativity = 1.9, .boiling_point = 5869.0, .melting_point = 3459.0, .ionization_energy = 760.0, .electron_affinity = 14.5, },
    { .element = 76, .molar_mass = 190.23, .electronegativity = 2.2, .boiling_point = 5285.0, .melting_point = 3306.0, .ionization_energy = 840.0, .electron_affinity = 106.1, },
    { .element = 77, .molar_mass = 192.22, .electronegativity = 2.2, .boiling_point = 4701.0, .melting_point = 2739.0, .ionization_energy = 880.0, .electron_affinity = 151.0, },
    { .element = 78, .molar_mass = 195.08, .electronegativity = 2.28, .boiling_point = 4098.0, .melting_point = 2041.4, .ionization_energy = 870.0, .electron_affinity = 205.3, },
    { .element = 79, .molar_mass = 196.97, .electronegativity = 2.54, .boiling_point = 3129.0, .melting_point = 1337.33, .ionization_energy = 890.1, .electron_affinity = 222.8, },
    { .element = 80, .molar_mass = 200.59, .electronegativity = 2.0, .boiling_point = 629.88, .melting_point = 234.32, .ionization_energy = 1007.1, .electron_affinity = 0.0, },
    { .element = 81, .molar_mass = 204.38, .electronegativity = 1.62, .boiling_point = 1746.0, .melting_point = 577.0, .ionization_energy = 589.4, .electron_affinity = 19.2, },
    { .element = 82, .molar_mass = 207.2, .electronegativity = 2.33, .boiling_point = 2022.0, .melting_point = 600.61, .ionization_energy = 715.6, .electron_affinity = 35.1, },
    { .element = 83, .molar_mass = 208.98, .electronegativity = 2.02, .boiling_point = 1837.0, .melting_point = 544.4, .ionization_energy = 703.0, .electron_affinity = 91.2, },
    { .element = 84, .molar_mass = 209.0, .electronegativity = 2.0, .boiling_point = 1235.0, .melting_point = 527.0, .ionization_energy = 812.1, .electron_affinity = 183.3, },
    { .element = 85, .molar_mass = 210.0, .electronegativity = 2.2, .boiling_point = 610.0, .melting_point = 575.0, .ionization_energy = 890.0, .electron_affinity = 270.1, },
    { .element = 86, .molar_mass = 222.0, .electronegativity = NaN, .boiling_point = 211.3, .melting_point = 202.0, .ionization_energy = 1037.0, .electron_affinity = 0.0, },
    { .element = 87, .molar_mass = 223.0, .electronegativity = 0.7, .boiling_point = 950.0, .melting_point = 300.0, .ionization_energy = 380.0, .electron_affinity = NaN, },
    { .element = 88, .molar_mass = 226.0, .electronegativity = 0.9, .boiling_point = 2010.0, .melting_point = 973.0, .ionization_energy = 509.3, .electron_affinity = NaN, },
    { .element = 89, .molar_mass = 227.0, .electronegativity = 1.1, .boiling_point = 3473.0, .melting_point = 1323.0, .ionization_energy = 499.0, .electron_affinity = NaN, },
    { .element = 90, .molar_mass = 232.04, .electronegativity = 1.3, .boiling_point = 5093.0, .melting_point = 2023.0, .ionization_energy = 587.0, .electron_affinity = NaN, },
    { .element = 91, .molar_mass = 231.04, .electronegativity = 1.5, .boiling_point = 4273.0, .melting_point = 1845.0, .ionization_energy = 568.0, .electron_affinity = NaN, },
    { .element = 92, .molar_mass = 238.03, .electronegativity = 1.38, .boiling_point = 4200.0, .melting_point = 1408.0, .ionization_energy = 597.6, .electron_affinity = NaN, },
    { .element = 93, .molar_mass = 237.0, .electronegativity = 1.36, .boiling_point = 4273.0, .melting_point = 917.0, .ionization_energy = 604.5, .electron_affinity = NaN, },
    { .element = 94, .molar_mass = 244.0, .electronegativity = 1.28, .boiling_point = 3503.0, .melting_point = 913.0, .ionization_energy = 584.7, .electron_affinity = NaN, },
    { .element = 95, .molar_mass = 243.0, .electronegativity = 1.3, .boiling_point = 2284.0, .melting_point = 1449.0, .ionization_energy = 578.0, .electron_affinity = NaN, },
    { .element = 96, .molar_mass = 247.0, .electronegativity = 1.3, .boiling_point = 3383.0, .melting_point = 1618.0, .ionization_energy = 581.0, .electron_affinity = NaN, },
    { .element = 97, .molar_mass = 247.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1323.0, .ionization_energy = 601.0, .electron_affinity = NaN, },
    { .element = 98, .molar_mass = 251.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1173.0, .ionization_energy = 608.0, .electron_affinity = NaN, },
    { .element = 99, .molar_mass = 252.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1133.0, .ionization_energy = 619.0, .electron_affinity = NaN, },
    { .element = 100, .molar_mass = 257.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1800.0, .ionization_energy = 627.0, .electron_affinity = NaN, },
    { .element = 101, .molar_mass = 258.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1100.0, .ionization_energy = 635.0, .electron_affinity = NaN, },
    { .element = 102, .molar_mass = 259.0, .electronegativity = 1.3, .boiling_point = NaN, .melting_point = 1100.0, .ionization_energy = 642.0, .electron_affinity = NaN, },
    { .element = 103, .molar_mass = 266.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = 1900.0, .ionization_energy = 470.0, .electron_affinity = NaN, },
    { .element = 104, .molar_mass = 267.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = 580.0, .electron_affinity = NaN, },
    { .element = 105, .molar_mass = 268.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 106, .molar_mass = 269.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 107, .molar_mass = 270.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 108, .molar_mass = 270.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 109, .molar_mass = 278.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 110, .molar_mass = 281.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 111, .molar_mass = 282.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 112, .molar_mass = 285.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 113, .molar_mass = 286.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 114, .molar_mass = 289.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 115, .molar_mass = 290.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 116, .molar_mass = 293.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 117, .molar_mass = 294.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN, },
    { .element = 118, .molar_mass = 294.0, .electronegativity = NaN, .boiling_point = NaN, .melting_point = NaN, .ionization_energy = NaN, .electron_affinity = NaN }
};

chemdb chemdbs[] = {
    { .name = "none", .description = "from Narnia", .data = 0 },
    { .name = "ptable", .description = "from ptable.com", .data = ptable_db },
    { .name = "merck", .description = "from the Kuei website", .data = 0 },
    { .name = "textbook", .description = "from the chem textbook", .data = 0 },
    { .name = "wikipedia", .description = "from wikipedia", .data = 0 },
};


const char * orbitals = "spdfghijklmnoqrtuvwxyzabceABCDEFGHIJKLMNOPQRSTUVWXYZ";

element_id element_count() {
    return ELEMENT_COUNT;
}

chemdb_id chemdb_count() {
    return CHEMDB_COUNT;
}

int element_econfig(client_index client, element_id element) {
    if (element > 192920) {
        socket_println(client, "That element cannot be config'd by the current orbital order (max = 19290).");
        return -1;
    }
    socket_println(client, "");
    socket_println(client, "Full electron config of %s:", element_name(element));
    unsigned long period = 1;
    unsigned long orbital = 0;
    unsigned long val = 0;
    unsigned long next_orb = 0;
    unsigned long next_per = 2;
    unsigned long next_tick = 0;
    unsigned long last_period = 1;
    unsigned long last_orbital = 0;
    unsigned long last_val = 0;
    while (element > 0) {
        last_period = period;
        last_orbital = orbital;
        last_val = val;
        val++;
        element--;
        if (val >= (4 * orbital + 2)) {
            socket_print(client, "%lu%c%lu ", period, orbitals[orbital], val);
            if (!orbital) {
                if (next_tick) {
                    period = next_per;
                    orbital = next_orb;
                    next_per++;
                } else {
                    period = next_per;
                    orbital = next_orb;
                    next_orb++;
                }
                next_tick = !next_tick;
            } else {
                orbital--;
                period++;
            }
            val = 0;
        }
    }
    if (val) {
        socket_println(client, "%lu%c%lu ", period, orbitals[orbital], val);
    }
    socket_println(client, "");
    socket_println(client, "Last electron quantum numbers:");
    socket_println(client, "(%lu, %lu, %+li, %s)", last_period, last_orbital, (last_val % (2 * last_orbital + 1)) - last_orbital, (last_val >= (last_orbital * 2 + 1)) ? "-1/2" : "+1/2");
    socket_println(client, "");
    return 0;
}

const char * element_econfig_order() {
    return orbitals;
}

char * element_name(element_id element) {
    if (element >= element_count()) {
        element = 0;
    }
    return elements[element].name;
}

unsigned element_number(element_id element) {
    return element;
}

char * element_symbol(element_id element) {
    if (element >= element_count()) {
        element = 0;
    }
    return elements[element].symbol;
}

int element_boiling_point(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].boiling_point;
    return 0;
}

int element_melting_point(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].melting_point;
    return 0;
}

int element_electron_affinity(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].electron_affinity;
    return 0;
}

int element_ionization_energy(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].ionization_energy;
    return 0;
}

int element_electronegativity(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].electronegativity;
    return 0;
}

int element_molar_mass(chemdb_id chemdb, element_id element, double * ret) {
    if (element >= element_count()) {
        element = 0;
    }
    (*ret) = chemdbs[chemdb].data[element].molar_mass;
    return 0;
}

char * chemdb_name(chemdb_id chemdb) {
    if (chemdb >= chemdb_count()) {
        chemdb = 0;
    }
    return chemdbs[chemdb].name;
}

char * chemdb_description(chemdb_id chemdb) {
    if (chemdb >= chemdb_count()) {
        chemdb = 0;
    }
    return chemdbs[chemdb].description;
}

int chemdb_good(client_index client, chemdb_id chemdb) {
    if ((!chemdb) || (chemdb >= chemdb_count())) {
        socket_println(client, "Select a database first.");
        return -1;
    } else if (!chemdbs[chemdb].data) {
        socket_println(client, "Akshay is lazy and has not filled this database yet (use ptable).");
        return -1;
    }
    return 0;
}


#include <include/typedefs.h>

element_id element_count();
chemdb_id chemdb_count();

int element_econfig(client_index, element_id);
const char * element_econfig_order();

char * element_name(element_id);
unsigned element_number(element_id);
char * element_symbol(element_id);

int element_boiling_point(chemdb_id, element_id, double *);
int element_melting_point(chemdb_id, element_id, double *);
int element_electron_affinity(chemdb_id, element_id, double *);
int element_ionization_energy(chemdb_id, element_id, double *);
int element_electronegativity(chemdb_id, element_id, double *);
int element_molar_mass(chemdb_id, element_id, double *);
int chemdb_good(client_index, chemdb_id);

char * chemdb_name(chemdb_id);
char * chemdb_description(chemdb_id);


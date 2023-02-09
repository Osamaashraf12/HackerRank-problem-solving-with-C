#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
	// first start with town name, then make post offices and in every office make packages
	printf("%s:\n", t.name);
	for (int i = 0; i < t.offices_count; i++) {
		
		
		printf("\t%d:\n", i);
		for (int j = 0; j < t.offices[i].packages_count; j++){
			printf("\t\t%s\n", t.offices[i].packages[j].id);
		}
	}
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
	
	post_office *SOURCE, *TARGET;
	int returned_count = 0;
	package *returned;
	returned = malloc(1);
	
	SOURCE = &(source->offices[source_office_index]);
	TARGET = &(target->offices[target_office_index]);
	
	for (int i = 0; i < SOURCE->packages_count; i++) {
		package pkg;
		pkg = SOURCE->packages[i];
		
		// check if pkg satisfies the conditions of the weight in the other post office
		if (pkg.weight >= TARGET->min_weight && pkg.weight <= TARGET->max_weight) {
			TARGET->packages_count++;
			TARGET->packages = (package *) realloc(TARGET->packages,
			sizeof(package)*TARGET->packages_count);
			TARGET->packages[TARGET->packages_count-1] = pkg;
		} else {
			returned_count++;
			returned = (package *) realloc(returned,
			sizeof(package)*returned_count);
			returned[returned_count-1] = pkg;
		}
	}

	free(SOURCE->packages);
	SOURCE->packages = returned;
	SOURCE->packages_count = returned_count;
	
}

town *town_with_most_packages(town *towns, int towns_count) {
	int packs, most_packs = 0, index;

	for (int i = 0; i < towns_count; i++) {
		packs = 0;

		for (int j = 0; j < towns[i].offices_count; j++) {
			packs += towns[i].offices[j].packages_count;
		}

		if (packs > most_packs) {
			most_packs = packs;
			index = i;
		}
	}

	return &towns[index];
}

town *find_town(town *towns, int towns_count, char *name) {
	town *current;

	for (int i = 0; i < towns_count; i++) {
		current = &towns[i];

		if (!strcmp(current->name, name))
		break;
	}

	return current;
}

int main(){
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
			case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
			case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
			case 3:
			printf("Town with the most number of packages is %s\n",
			(*town_with_most_packages(towns, towns_count)).name);
			break;
		}
	}
	return 0;
}

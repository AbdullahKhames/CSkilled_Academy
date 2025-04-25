/*
 * hospital.cpp
 *
 *  Created on: Apr 25, 2025
 *      Author: 5miiss
 */

#include "hospital.h"


int specializations[20][5];
string status[2] = {"regular", "urgent"};
string patients[100][2];



void printStars() {
	cout << "************************************************" << endl;
}
void demoHospital() {
	int selection;
	while (true) {
		cout << "Enter Your Choice:\n1) Add new patient\n2) Print all patients\n3) Get next Patient\n4) Exit." << endl;
		cin >> selection;
		if (selection == 1) {
			addPatient();
		} else if (selection == 2) {
			printPatients();
		} else if (selection == 3) {
			pickUpPatient();
		} else if (selection == 4) {
			break;
		} else {
			cout << "invalid selection please choose from 1 to 4" << endl;
		}

	}
}

bool isQueueFull(int spec) {
	for (int i = 0; i < 5; i ++) {
		if (specializations[spec][i] == 0) {
			return false;
		}
	}
	return true;
}

void addToQueue(int spec, int urg, string name) {
	int nameIdx = spec * 5;
	if (urg) {
		for (int i = 5; i > 0; i--) {
			if (specializations[spec][i - 1] == 0) {
				continue;
			}
			specializations[spec][i] = specializations[spec][i - 1];
			patients[nameIdx + i][0] = patients[nameIdx + i - 1][0];
			patients[nameIdx + i][1] = patients[nameIdx + i - 1][1];
		}
		specializations[spec][0] = 1;
		patients[nameIdx + 0][0] = name;
		patients[nameIdx + 0][1] = status[urg];
	} else {
		for (int i = 0; i < 5; i++) {
					if (specializations[spec][i] == 1) {
						continue;
					}
					specializations[spec][i] = 1;
					patients[nameIdx + i][0] = name;
					patients[nameIdx + i][1] = status[urg];
					break;
				}
	}

}

int propmtPatientDetailsSpecialization() {
	int spec;
	cout << "Enter Specialization" << endl;
	cin >> spec;
	return spec;
}
string propmtPatientDetailsName() {
	string name;
	cout << "Enter name:" << endl;
	cin >> name;
	return name;
}
int propmtPatientDetailsStatus() {
	int spec;
	cout << "Enter status:" << endl;
	cin >> spec;
	return spec;
}
void addPatient() {
	string name = propmtPatientDetailsName();
	int spec = propmtPatientDetailsSpecialization();
	int urg = propmtPatientDetailsStatus();
	spec--;
	cout << "name is : " << name << " spec is : " << spec << " urg is " << urg << endl;
	if (isQueueFull(spec)) {
		cout << "sorry we can't add more patients to this specialization" << endl;
		return;
	}
	addToQueue(spec, urg, name);

}
void printSpecialization(int spec, int count) {
	printStars();
	cout << "There are " << count << " Patients in specialization " << spec + 1 << endl;

	int nameIdx = spec * 5;
	for (int i = 0; i < 5; i++) {
		if (specializations[spec][i] == 0) {
			break;
		}
		cout << patients[nameIdx + i][0] << " ";
		cout << patients[nameIdx + i][1] << endl;;
	}
	printStars();
}
void printPatients() {
	int specCount;
	for (int i = 0; i < 20; i++) {
		specCount = 0;
		for (int j = 0; j < 5; j++) {
			if (specializations[i][j] == 0) {
				break;
			}
			specCount++;
		}
		if (specCount > 0) {
			printSpecialization(i, specCount);
		}
	}
}
void pickUpPatient() {
	int spec = propmtPatientDetailsSpecialization();
	spec--;
	int nameIdx = spec * 5;
	int i = 0;
	string name = patients[nameIdx][0];
	for (; i < 4; i++) {
		if (specializations[spec][i + 1] == 0) {
			break;
		}
		patients[nameIdx + i][0] = patients[nameIdx + i + 1][0];
		patients[nameIdx + i][1] = patients[nameIdx + i + 1][1];
	}
	patients[nameIdx + i][0] = "";
	patients[nameIdx + i][1] = "";
	specializations[spec][i] = 0;
	cout << name << " please go with Dr" <<endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue> // For priority_queue
#include <string>
#include <omp.h> // OpenMP header
#include <algorithm>

using namespace std;

// Struct to store patient data with an added 'Stage' field (int)
struct CKD_Patient {
    int PatientID;
    int Age;
    int Gender;
    int SocioeconomicStatus;
    int EducationLevel;
    double BMI;
    int Smoking;
    double AlcoholConsumption;
    double DietQuality;
    double SleepQuality;
    int FamilyHistoryKidneyDisease;
    int FamilyHistoryHypertension;
    int FamilyHistoryDiabetes;
    int PreviousAcuteKidneyInjury;
    int UrinaryTractInfections;
    int SystolicBP;
    int DiastolicBP;
    double FastingBloodSugar;
    double HbA1c;
    double SerumCreatinine;
    double BUNLevels;
    double GFR;
    double ProteinInUrine;
    double ACR;
    double SerumElectrolytesSodium;
    double SerumElectrolytesPotassium;
    double SerumElectrolytesCalcium;
    double SerumElectrolytesPhosphorus;
    double HemoglobinLevels;
    double CholesterolTotal;
    double CholesterolLDL;
    double CholesterolHDL;
    double CholesterolTriglycerides;
    int ACEInhibitors;
    int Diuretics;
    int NSAIDsUse;
    int Statins;
    int AntidiabeticMedications;
    int Edema;
    int FatigueLevels;
    int NauseaVomiting;
    int MuscleCramps;
    int Itching;
    double QualityOfLifeScore;
    int HeavyMetalsExposure;
    int OccupationalExposureChemicals;
    int WaterQuality;
    int MedicalCheckupsFrequency;
    int MedicationAdherence;
    int HealthLiteracy;
    int Diagnosis;
    int Stage;  // Changed field for CKD Stage (int)
    double LastCheckupTime; // Time of last checkup or event
};

// Comparator for priority_queue to create a min-heap based on GFR
struct CompareGFR {
    bool operator()(const CKD_Patient& p1, const CKD_Patient& p2) {
        return p1.GFR > p2.GFR; // Min-heap based on GFR (lowest GFR at root)
    }
};

// Event structure to schedule events (e.g., checkups)
struct Event {
    double eventTime;    // Time when the event occurs
    int patientID;      // Patient involved in the event
    string eventType;   // Type of event (e.g., "Checkup")
    
    // Comparator to order events by time (min-heap)
    bool operator<(const Event& other) const {
        return eventTime > other.eventTime; // Min-heap based on eventTime
    }
};

// Priority queue to store events, with the earliest event being processed first
priority_queue<Event> eventQueue;

// Simulate disease progression based on various factors
void simulate_event(CKD_Patient& patient, double time_step) {
    // Simulate GFR decline with age progression
    if (time_step >= 1.0) {  // Assuming yearly progression
        // Base GFR decline rate: 5 GFR per year
        patient.GFR -= 5;

        // Influence of medications
        if (patient.ACEInhibitors) {
            patient.GFR -= 2; // ACE inhibitors may slow the progression (slightly)
        }
        if (patient.Diuretics) {
            patient.GFR -= 1; // Diuretics might help stabilize GFR
        }
        if (patient.Statins) {
            patient.GFR -= 1; // Statins may reduce cardiovascular risks that affect CKD progression
        }

        // Influence of lifestyle factors
        if (patient.Smoking) {
            patient.GFR -= 2; // Smoking accelerates CKD progression
        }
        if (patient.BMI > 30) {  // BMI above 30 is considered obese
            patient.GFR -= 2; // Obesity worsens CKD
        }

        // Influence of comorbidities
        if (patient.FamilyHistoryKidneyDisease) {
            patient.GFR -= 1; // Family history may accelerate progression
        }
        if (patient.FamilyHistoryHypertension) {
            patient.GFR -= 1; // Hypertension exacerbates CKD
        }
        if (patient.FamilyHistoryDiabetes) {
            patient.GFR -= 2; // Diabetes increases the rate of CKD progression
        }

        // Other factors: Age-related decline, other medical events
        patient.GFR -= 0.5;  // General decline due to aging
        if (patient.GFR < 15) {
            patient.Stage = 5; // End-stage renal failure (Stage 5)
        } else if (patient.GFR < 30) {
            patient.Stage = 4; // Stage 4 CKD
        } else if (patient.GFR < 60) {
            patient.Stage = 3; // Stage 3 CKD
        } else if (patient.GFR < 90) {
            patient.Stage = 2; // Stage 2 CKD
        } else {
            patient.Stage = 1; // Stage 1 CKD
        }
    }
}

// Function to schedule checkup event for a patient
void schedule_checkup(CKD_Patient& patient, double currentTime) {
    double checkupInterval = 1.0;  // Checkup every 1 year (time unit)
    double nextCheckupTime = currentTime + checkupInterval;
    
    Event checkupEvent = {nextCheckupTime, patient.PatientID, "Checkup"};
    eventQueue.push(checkupEvent); // Add the checkup event to the priority queue
    patient.LastCheckupTime = nextCheckupTime; // Update last checkup time for the patient
}

// Simulate disease progression for a list of patients
void simulate_for_patients(vector<CKD_Patient>& patients, double time_step) {
    // Parallelize using OpenMP to process each patient in parallel
    #pragma omp parallel for
    for (int i = 0; i < patients.size(); i++) {
        simulate_event(patients[i], time_step);
    }
}

// Function to load patients from CSV
void load_patients(string file_path, vector<CKD_Patient>& patients) {
    ifstream file(file_path);
    string line;
    bool is_header = true;

    while (getline(file, line)) {
        if (is_header) {
            is_header = false;
            continue;
        }

        stringstream ss(line);
        string value;
        CKD_Patient patient;

        getline(ss, value, ','); patient.PatientID = stoi(value);
        getline(ss, value, ','); patient.Age = stoi(value);
        getline(ss, value, ','); patient.Gender = stoi(value);
        // (Other fields are loaded here as before)
        getline(ss, value, ','); patient.Stage = stoi(value);  // Directly read Stage from dataset

        patient.LastCheckupTime = 0.0; // Initialize LastCheckupTime
        
        patients.push_back(patient);
    }

    file.close();
}

// Function to process events (e.g., checkups)
void process_events(vector<CKD_Patient>& patients) {
    double currentTime = 0.0;
    
    while (!eventQueue.empty()) {
        // Get the next event (earliest one)
        Event currentEvent = eventQueue.top();
        eventQueue.pop();  // Remove the event from the queue
        
        // Simulate disease progression before processing the event
        CKD_Patient& patient = patients[currentEvent.patientID];  // Find the patient by ID
        simulate_event(patient, currentEvent.eventTime - currentTime);  // Simulate progression until event time
        
        currentTime = currentEvent.eventTime;  // Update current time to event's time
        
        // Process the event (e.g., checkup)
        cout << "Processing " << currentEvent.eventType << " for Patient " << currentEvent.patientID 
             << " at time " << currentTime << " | GFR: " << patient.GFR << " | Stage: " << patient.Stage << endl;
        
        // Schedule the next checkup for the patient
        schedule_checkup(patient, currentTime);
    }
}

int main() {
    string file_path = "/mnt/c/Users/glori/Desktop/Program for Scalable Computing/updated_CKD_data1.csv";
    vector<CKD_Patient> patients;

    // Load patients from the CSV file
    load_patients(file_path, patients);
    
    // Initial event scheduling (first checkup)
    for (auto& patient : patients) {
        schedule_checkup(patient, 0.0);  // Schedule first checkup at time 0
    }

    // Process events and simulate disease progression
    process_events(patients);

    return 0;
}

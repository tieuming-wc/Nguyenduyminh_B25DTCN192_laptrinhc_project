#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // ham su ly ki tu
#define MAX 100
// ===== Cau truc du lieu =====
struct Patient {
    char cardId[10];   // Ma ho so / CCCD
    char name[50];     // Ten benh nhan (luu chu thuong)
    char phone[15];    // So dien thoai
    double debt;       // Tien vien phi (con no)
    int visitDays;     // So lan kham
    char admitDate[11]; // Ngay nhap vien dd/mm/yyyy
    char dischargeDate[11]; // Ngay xuat vien dd/mm/yyyy (empty neu chua xuat)
};

struct Record {
    char cardId[10];   // Ma ho so
    int visitNumber;   // So lan kham
    char visitDate[11]; // Ngay kham dd/mm/yyyy
};
// ===== Du lieu mau =====
struct Patient patients[MAX] = {
    {"BN001", "Nguyen Tien Hung",       "0901123456", 120000, 2, "01/11/2025", ""},
    {"BN002", "Nguyen Tri Hung",        "0902456789",  50000, 1, "29/11/2025", ""},
    {"BN003", "Nguyen Tuan Hung",       "0912345678", 200000, 3, "16/12/2025", ""},
    {"BN004", "Nguyen Viet Hung",       "0938765432",  75000, 1, "25/04/2025", ""},
    {"BN005", "Chu Gia Huy",            "0987654321", 310000, 4, "12/06/2025", ""},
    {"BN006", "Phung Quang Huy",        "0971122334", 150000, 2, "22/07/2025", ""},
    {"BN007", "Dieu Bao Thai Khang",    "0965566778",  90000, 1, "30/07/2025", ""},
    {"BN008", "Nguyen Bao Khanh",       "0949988776", 420000, 3, "09/11/2025", ""},
    {"BN009", "Nguyen Vo Trung Kien",   "0911998877",  65000, 1, "06/04/2025", ""},
    {"BN010", "Ta Thanh Long",          "0923778899", 230000, 2, "04/03/2025", ""},
    {"BN011", "Mai Quan Minh",          "0934455667", 170000, 1, "22/04/2025", ""},
    {"BN012", "Nguyen Hong Minh",       "0962233445", 280000, 2, "12/05/2025", ""},
    {"BN013", "Nguyen Duy Minh",        "0973665544",  95000, 3, "07/01/2025", ""},
    {"BN014", "Do Thanh Nga",           "0984123567", 330000, 2, "22/01/2025", ""},
    {"BN015", "Nguyen Thi Kim Ngan",    "0908899776",  80000, 1, "04/07/2025", ""}
};

struct Record records[MAX] = {
    {"BN001", 1, "01/11/2025"},
    {"BN001", 2, "03/11/2025"},
    {"BN002", 1, "29/11/2025"},
    {"BN003", 1, "16/12/2025"},
    {"BN003", 2, "18/12/2025"},
    {"BN003", 3, "20/12/2025"},
    {"BN004", 1, "25/04/2025"},
    {"BN005", 1, "12/06/2025"},
    {"BN005", 2, "14/06/2025"},
    {"BN005", 3, "15/06/2025"},
    {"BN005", 4, "18/06/2025"},
    {"BN006", 1, "22/07/2025"},
    {"BN006", 2, "25/07/2025"},
    {"BN007", 1, "30/07/2025"},
    {"BN008", 1, "09/11/2025"},
    {"BN008", 2, "11/11/2025"},
    {"BN008", 3, "13/11/2025"},
    {"BN009", 1, "06/04/2025"},
    {"BN010", 1, "04/03/2025"},
    {"BN010", 2, "06/03/2025"},
    {"BN011", 1, "22/04/2025"},
    {"BN012", 1, "12/05/2025"},
    {"BN012", 2, "14/05/2025"},
    {"BN013", 1, "07/01/2025"},
    {"BN013", 2, "09/01/2025"},
    {"BN013", 3, "11/01/2025"},
    {"BN014", 1, "22/01/2025"},
    {"BN014", 2, "24/01/2025"},
    {"BN015", 1, "04/07/2025"}
};
int count = 15; 
int recordCount = 31;
// ===== khai bao truoc ham =====
void swapPatients(struct Patient *a, struct Patient *b);
void addPatient();             // themBenhNhan
void updatePatientList();      // CapnhatdanhSachBenhNhan
void dischargePatient();       // Xuatvien
void displayPatientList();     // Hienthidanhsachbenhnhan
void searchPatient();          // Timkiembenhnhan
void sortPatientList();        // Sapxepdanhsachbenhnhan
void recordMedicalVisit();     // Ghinhankhambenh
void viewMedicalHistory();     // Xemlichsukhambenh
// ===== Ham ho tro =====
void swapPatients(struct Patient *a, struct Patient *b){
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Chuyen chuoi sang chu thuong
void toLowerStr(char *s){
    for(int i=0; s[i]; i++){
        s[i] = tolower((unsigned char)s[i]);
    }
}

// Ham kiem tra ngay co dang dd/mm/yyyy (co ban)
int validDateFormat(const char *d){
    if(strlen(d)!=10) return 0;
    if(!isdigit(d[0])||!isdigit(d[1])||d[2]!='/') return 0;
    if(!isdigit(d[3])||!isdigit(d[4])||d[5]!='/') return 0;
    if(!isdigit(d[6])||!isdigit(d[7])||!isdigit(d[8])||!isdigit(d[9])) return 0;
    return 1;
}

// Nhap mot chuoi (fgets) va cat newline
void inputStr(char *buf, int len){
    if(fgets(buf, len, stdin)){
        buf[strcspn(buf, "\n")] = 0;
    } else {
        buf[0]=0;
    }
}

// Nhap so thuc (double) tu nguoi dung, khong cho am
double inputDoubleNonNegative(){
    char buf[64];
    double val;
    while(1){
        inputStr(buf, sizeof(buf));
        if(strlen(buf)==0){ printf("Invalid input. Please enter again: "); continue; }
        val = atof(buf);
        if(val < 0){
            printf("Amount cannot be negative. Please enter again: ");
            continue;
        }
        return val;
    }
}

// ===== Ham chuc nang (giu lai cac void theo yeu cau) =====
void addPatient() {
    printf("\n>>> Function: Add new patient\n");
}
void updatePatientList() {
    printf("\n>>> Function: Update patient information\n");
}
void dischargePatient() {
    printf("\n>>> Function: Discharge patient\n");
}
void displayPatientList() {
    printf("\n>>> Function: Display patient list\n");
}
void searchPatient() {
    printf("\n>>> Function: Search patient\n");
}
void sortPatientList() {
    printf("\n>>> Function: Sort patient list\n");
}
void recordMedicalVisit() {
    printf("\n>>> Function: Record medical visit\n");
}
void viewMedicalHistory() {
    printf("\n>>> Function: View medical history\n");
}

// ===== Main =====
int main() {
    int choice;
    struct Patient p;
    p.cardId[0]='\0'; p.name[0]='\0'; p.phone[0]='\0';
    p.debt=0.0; p.visitDays=0;
    p.admitDate[0]=0; p.dischargeDate[0]=0;

    char input[32];

    do {
        system("cls");
        printf("\n======================================================\n");
        printf("|                  HOSPITAL SYSTEM                    |\n");
        printf("======================================================\n");
        printf("|  1 | Add new patient                                |\n");
        printf("|  2 | Update patient information                     |\n");
        printf("|  3 | Discharge patient                              |\n");
        printf("|  4 | Display patient list                           |\n");
        printf("|  5 | Search patient                                 |\n");
        printf("|  6 | Sort patient list                              |\n");
        printf("|  7 | Record medical visit                           |\n");
        printf("|  8 | View medical history                           |\n");
        printf("|  0 | Exit                                           |\n");
        printf("======================================================\n");
        printf("Enter your choice: ");
        inputStr(input, sizeof(input));
        if(strlen(input)==0){
            printf("Ban chua chon, xin hay chon!\n");
            system("pause");
            continue;
        }
        if(strlen(input)!=1 || input[0]<'0' || input[0]>'8'){
            printf("Lua chon khong hop le!\n");
            system("pause");
            continue;
        }
        choice = input[0]-'0';
        switch(choice){
        	
// ===== CASE 1: Them benh nhan =====
        case 1:
            addPatient();
            if (count >= MAX) {
                printf("The list is full. Cannot add more patients!\n");
                system("pause");
                break;
            }
            printf("\n=== ADD NEW PATIENT ===\n");
// Nhap CCCD, khong duoc trung
            while(1){
                printf("Enter CCCD: ");
                inputStr(patients[count].cardId, sizeof(patients[count].cardId));
                if(strlen(patients[count].cardId) == 0){ 
                    printf("Cannot be empty. "); continue; 
                }
                int dup = 0;
                for(int i = 0; i < count; i++){
                    if(strcmp(patients[i].cardId, patients[count].cardId) == 0){
                        dup = 1; break;
                    }
                }
                if(dup){ 
                    printf("CCCD already exists, please enter again!\n"); 
                    continue; 
                }
                break;
            }
// Nhap ten, bat buoc
            while(1){
                printf("Enter name: ");
                inputStr(patients[count].name, sizeof(patients[count].name));
                if(strlen(patients[count].name) == 0){ 
                    printf("Cannot be empty. "); continue; 
                }
                toLowerStr(patients[count].name);
                break;
            }
// Nhap SDT 9 so
            while(1){
                printf("Enter phone number (9 digits): ");
                inputStr(patients[count].phone, sizeof(patients[count].phone));
                if(strlen(patients[count].phone) != 9){ 
                    printf("Phone number must be 9 digits. Try again.\n"); 
                    continue; 
                }
                int ok = 1;
                for(size_t k = 0; k < strlen(patients[count].phone); k++){
                    if(!isdigit((unsigned char)patients[count].phone[k])){ ok = 0; break; }
                }
                if(!ok){ 
                    printf("Phone number must contain digits only. Try again.\n"); 
                    continue; 
                }
                break;
            }
// Nhap ngay nhap vien
            while(1){
                printf("Enter admission date (dd/mm/yyyy): ");
                inputStr(patients[count].admitDate, sizeof(patients[count].admitDate));
                if(!validDateFormat(patients[count].admitDate)){ 
                    printf("Invalid date format. Try again.\n"); 
                    continue; 
                }
                break;
            }
// Khoi tao cong no =0 va so ngay kham theo yeu cau
            patients[count].debt = 0.0;
            patients[count].visitDays = 0;
            patients[count].dischargeDate[0] = 0;
            count++;
// Hien thi bang thong tin vua them (bang 1 dong)
            printf("\n--- Newly added patient (one row) ---\n");
            printf("| %-10s | %-20s | %-10s | %-10s | %-5s | %-11s |\n",
                   "CCCD", "Name", "Phone", "DEBT", "Visits", "Admission");
            printf("----------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                   patients[count-1].cardId, patients[count-1].name, patients[count-1].phone,
                   patients[count-1].debt, patients[count-1].visitDays, patients[count-1].admitDate);
            printf("----------------------------------------------------------------\n");
            system("pause");
            break;

            
// ===== CASE 2: Cap nhat danh sach =====
        case 2:
            updatePatientList();
            printf("\n=== UPDATE PATIENT INFORMATION ===\n");
            {
                char id[10];
                int foundIndex = -1;
                while(1){
                    printf("Enter patient CCCD: ");
                    inputStr(id, sizeof(id));
                    if(strlen(id)==0){ 
                        printf("Cannot be empty. "); continue; 
                    }
                    break;
                }
// Tim benh nhan theo CCCD
                for (int i = 0; i < count; i++) {
                    if (strcmp(patients[i].cardId, id) == 0) {
                        foundIndex = i;
                        break;
                    }
                }
                if (foundIndex == -1) {
                    printf("Patient with CCCD %s not found.\n", id);
                    system("pause");
                    break;
                }
// Nhap ten moi, bat buoc
                while(1){
                    printf("Enter patient name: ");
                    inputStr(patients[foundIndex].name, sizeof(patients[foundIndex].name));
                    if(strlen(patients[foundIndex].name)==0){ 
                        printf("Cannot be empty. "); continue; 
                    }
                    toLowerStr(patients[foundIndex].name);
                    break;
                }
// Nhap SDT 9 so
                while(1){
                    char phoneBuf[15];
                    int valid = 1;
                    printf("Enter phone number (9 digits): ");
                    inputStr(phoneBuf, sizeof(phoneBuf));
                    if(strlen(phoneBuf)!=9){ 
                        printf("Phone number must have 9 digits. Try again.\n"); continue; 
                    }
                    for(size_t k=0;k<strlen(phoneBuf);k++){
                        if(!isdigit((unsigned char)phoneBuf[k])){ valid=0; break; }
                    }
                    if(!valid){ 
                        printf("Phone number can only contain digits. Try again.\n"); continue; 
                    }
                    strcpy(patients[foundIndex].phone, phoneBuf);
                    break;
                }
// Co the cap nhat ngay nhap neu can (khong bat buoc)
                printf("Do you want to update admit date? (y/n): ");
                inputStr(input, sizeof(input));
                if(input[0]=='y' || input[0]=='Y'){
                    while(1){
                        printf("Enter new admit date (dd/mm/yyyy): ");
                        inputStr(patients[foundIndex].admitDate, sizeof(patients[foundIndex].admitDate));
                        if(!validDateFormat(patients[foundIndex].admitDate)){ 
                            printf("Invalid date format. Try again.\n"); continue; 
                        }
                        break;
                    }
                }
// Hien thi bang thong tin sau khi cap nhat (mot dong)
                printf("\n--- Updated patient information ---\n");
                printf("----------------------------------------------------------------\n");
                printf("| %-10s | %-20s | %-10s | %-10s | %-5s | %-11s |\n",
                       "CCCD", "Name", "Phone", "Debt", "Visits", "Admit Date");
                printf("| %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                       patients[foundIndex].cardId, patients[foundIndex].name, patients[foundIndex].phone,
                       patients[foundIndex].debt, patients[foundIndex].visitDays, patients[foundIndex].admitDate);
                printf("----------------------------------------------------------------\n");
                system("pause");
            }
            break;
            
// ===== CASE 3: Xuat vien =====
        case 3:
            dischargePatient();
            printf("\n=== DISCHARGE PATIENT ===\n");
            if(count==0){
                printf("No patients in the system!\n");
                system("pause");
                break;
            }
            {
                char id[10];
                int found = -1;
                printf("Enter patient CCCD: ");
                inputStr(id, sizeof(id));
// Tim benh nhan
                for(int i=0;i<count;i++){
                    if(strcmp(patients[i].cardId,id)==0){
                        found = i;
                        break;
                    }
                }
                if(found==-1){
                    printf("Patient not found!\n");
                    system("pause");
                    break;
                }
// In thong tin dang o dang bang
                printf("\n--- Patient Information ---\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("| %-10s | %-20s | %-10s | %-10s | %-5s | %-11s | %-11s |\n",
                       "CCCD","Name","Phone","Debt","Visits","Admit Date","Discharge Date");
                printf("| %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s | %-11s |\n",
                       patients[found].cardId, patients[found].name, patients[found].phone,
                       patients[found].debt, patients[found].visitDays,
                       patients[found].admitDate,
                       patients[found].dischargeDate[0]?patients[found].dischargeDate:"(not discharged)");
                printf("--------------------------------------------------------------------------------\n");
// Neu con cong no -> phai thanh toan (khong cho xuat vien)
                while(patients[found].debt > 0.0){
                    printf("Patient has remaining debt: %.2f VND\n", patients[found].debt);
                    printf("Choose payment method: 1-CASH | 2-BANK TRANSFER\n");
                    printf("Enter choice (1/2): ");
                    inputStr(input, sizeof(input));
                    
                    if(!(input[0]=='1' || input[0]=='2')){ 
                        printf("Invalid choice. Try again.\n"); continue; }
                    printf("Enter payment amount: ");
                    double pay = inputDoubleNonNegative();
                    if(pay <= 0.0){ printf("Amount must be > 0. Try again.\n"); continue; }
                    if(pay >= patients[found].debt){
                        double change = pay - patients[found].debt;
                        printf("Paid %.2f. Change: %.2f\n", patients[found].debt, change);
                        patients[found].debt = 0.0;
                    } else {
                        patients[found].debt -= pay;
                        printf("Paid %.2f. Remaining debt: %.2f\n", pay, patients[found].debt);
                    }
                }
// Khi cong no = 0 -> nhap ngay xuat vien va remove benh nhan
                while(1){
                    printf("Enter discharge date (dd/mm/yyyy): ");
                    inputStr(patients[found].dischargeDate, sizeof(patients[found].dischargeDate));
                    if(!validDateFormat(patients[found].dischargeDate)){ 
                        printf("Invalid date format. Try again.\n"); continue; 
                    }
                    break;
                }
// In hoa don / bang xac nhan
                printf("\n--- DISCHARGE CONFIRMATION ---\n");
                printf("---------------------------------------------------------------\n");
                printf("| %-10s | %-20s | %-11s | %-11s |\n", "CCCD","Name","Admit Date","Discharge Date");
                printf("| %-10s | %-20s | %-11s | %-11s |\n",
                       patients[found].cardId, patients[found].name, patients[found].admitDate, patients[found].dischargeDate);
                printf("---------------------------------------------------------------\n");
// Xoa benh nhan khoi mang
                for(int j=found;j<count-1;j++){
                    patients[j]=patients[j+1];
                }
                count--;
                printf(">>> Patient discharged successfully!\n");
                system("pause");
            }
            break;

// ===== CASE 4: Hien thi danh sach =====
        case 4:
            displayPatientList();
            if(count==0){
                printf("No patients!\n");
                system("pause");
                break;
            }
            {
                int pages = (count + 9) / 10; // so trang co that su
                int page = 1;
                char pageInput[16];

                while(1){
                    printf("\nTotal %d pages (10 patients/page). Enter page (1-%d) | 0 to exit: ", pages, pages);
                    inputStr(pageInput, sizeof(pageInput));
                    page = atoi(pageInput);
                    if(page==0) break;
                    if(page < 1 || page > pages){ 
                        printf("Invalid page! Choose 1-%d\n", pages); continue; }
                    system("cls");
                    printf("\n================== PAGE %d / %d ==================\n", page, pages);
                    printf("-------------------------------------------------------------------------------\n");
                    printf("| %-3s | %-10s | %-20s | %-10s | %-10s | %-5s| %-11s |\n",
                           "No","CCCD","Name","Phone","Debt","Visits","Admit Date");
                    int start = (page-1)*10;
                    int end = start + 10;
                    if(end > count) end = count;
                    for(int i = start; i < end; i++){
                        printf("| %-3d | %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                               i+1, patients[i].cardId, patients[i].name, patients[i].phone,
                               patients[i].debt, patients[i].visitDays, patients[i].admitDate);
                    }
                    printf("-------------------------------------------------------------------------------\n");
                }
            }
            break;

// ===== CASE 5: Tim kiem =====
        case 5:
            searchPatient();
            if(count==0){
                printf("No patients in the list!\n");
                system("pause");
                break;
            }
            {
                char keyword[50];
                int found=0;
                do{
                    printf("Enter patient name to search: ");
                    inputStr(keyword, sizeof(keyword));
                }while(strlen(keyword)==0);
// chuyen keyword sang thuong de tim de dang hon (patients da luu ten thuong)
                toLowerStr(keyword);
                printf("\n=== SEARCH RESULTS ===\n");
                printf("-------------------------------------------------------------------------------\n");
                printf("| %-3s | %-10s | %-20s | %-10s | %-10s | %-5s | %-11s |\n",
                       "No","CCCD","Name","Phone","Debt","Visits","Admit Date");
                for(int i=0;i<count;i++){
// tim theo ten (da luu chu thuong)
                    if(strstr(patients[i].name, keyword) != NULL){
                        printf("| %-3d | %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                               i+1, patients[i].cardId, patients[i].name, patients[i].phone,
                               patients[i].debt, patients[i].visitDays, patients[i].admitDate);
                        found = 1;
                    }
                }
                if(!found) printf("No patients found!\n");
                printf("-------------------------------------------------------------------------------\n");
                system("pause");
            }
            break;

// ===== CASE 6: Sap xep =====
        case 6:
            sortPatientList();
            if(count<2){
                printf("Not enough patients to sort!\n");
                system("pause");
                break;
            }
            {
                char sortInput[10];
                int mode;
                printf("Choose sorting type: 1-Name A->Z | 2-Debt Asc | 3-Debt Desc: ");
                inputStr(sortInput, sizeof(sortInput));
                mode = atoi(sortInput);
                if(mode==1){
                    for(int i=0;i<count-1;i++){
                        for(int j=i+1;j<count;j++){
                            if(strcmp(patients[i].name, patients[j].name) > 0){
                                swapPatients(&patients[i], &patients[j]);
                            }
                        }
                    }
                    printf(">>> Sorted by name A->Z!\n");
                } else if(mode==2){
                    for(int i=0;i<count-1;i++){
                        for(int j=i+1;j<count;j++){
                            if(patients[i].debt > patients[j].debt) swapPatients(&patients[i], &patients[j]);
                        }
                    }
                    printf(">>> Sorted by debt ascending!\n");
                } else if(mode==3){
                    for(int i=0;i<count-1;i++){
                        for(int j=i+1;j<count;j++){
                            if(patients[i].debt < patients[j].debt) swapPatients(&patients[i], &patients[j]);
                        }
                    }
                    printf(">>> Sorted by debt descending!\n");
                } else {
                    printf("Invalid choice!\n");
                }
// Hien thi 10 dong dau tien sau khi sap xep
                printf("\n--- First 10 patients after sorting ---\n");
                printf("-------------------------------------------------------------------------------\n");
                printf("| %-3s | %-10s | %-20s | %-10s | %-10s | %-5s | %-11s |\n",
                       "No","CCCD","Name","Phone","Debt","Visits","Admit Date");
                printf("-------------------------------------------------------------------------------\n");
                int limit = count < 10 ? count : 10;
                for(int i=0;i<limit;i++){
                    printf("| %-3d | %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                           i+1, patients[i].cardId, patients[i].name, patients[i].phone,
                           patients[i].debt, patients[i].visitDays, patients[i].admitDate);
                }
                printf("-------------------------------------------------------------------------------\n");
                system("pause");
            }
            break;

// ===== CASE 7: Ghi nhan kham =====
        case 7:
            recordMedicalVisit();
            if (count == 0) {
                printf("No patients in the system!\n");
                system("pause");
                break;
            }
            {
                char id[10];
                int found = -1;
                printf("Enter patient CCCD to record visit: ");
                inputStr(id, sizeof(id));
// Tim benh nhan
                for (int i = 0; i < count; i++) {
                    if (strcmp(patients[i].cardId, id) == 0) {
                        found = i;
                        break;
                    }
                }
                if (found == -1) {
                    printf("Patient with CCCD %s not found!\n", id);
                    system("pause");
                    break;
                }
// Nhap ngay kham
                char vdate[11];
                while(1){
                    printf("Enter visit date (dd/mm/yyyy): ");
                    inputStr(vdate, sizeof(vdate));
                    if(!validDateFormat(vdate)){ 
                        printf("Invalid date format. Try again.\n"); continue; 
                    }
                    break;
                }
// Tang so lan kham va luu record
                patients[found].visitDays++;
                strcpy(records[recordCount].cardId, id);
                records[recordCount].visitNumber = patients[found].visitDays;
                strncpy(records[recordCount].visitDate, vdate, sizeof(records[recordCount].visitDate)-1);
                records[recordCount].visitDate[10]=0;
                recordCount++;
// Neu kham phat sinh phi (neu muon)
                printf(">>> Visit recorded successfully! Total visits: %d\n", patients[found].visitDays);
// Hien thi dong thong tin benh nhan sau khi ghi nhan
                printf("\n--- Patient info after recording visit ---\n");
                printf("----------------------------------------------------------------\n");
                printf("| %-10s | %-20s | %-10s | %-10s | %-5s | %-11s |\n",
                       "CCCD","Name","Phone","Debt","Visits","Admit Date");
                printf("| %-10s | %-20s | %-10s | %-10.2f | %-5d | %-11s |\n",
                       patients[found].cardId, patients[found].name, patients[found].phone,
                       patients[found].debt, patients[found].visitDays, patients[found].admitDate);
                printf("----------------------------------------------------------------\n");
                system("pause");
            }
            break;

// ===== CASE 8: Xem lich su kham =====
        case 8:
            viewMedicalHistory();
            if (count == 0) {
                printf("No patients in the system!\n");
                system("pause");
                break;
            }
            {
                char id[10];
                int foundPatient = 0;
                printf("Enter patient CCCD to view visit history: ");
                inputStr(id, sizeof(id));
// Kiem tra benh nhan co ton tai va in ten tren bang
                char patientName[50] = "";
                for (int i = 0; i < count; i++) {
                    if (strcmp(patients[i].cardId, id) == 0) {
                        foundPatient = 1;
                        strncpy(patientName, patients[i].name, sizeof(patientName)-1);
                        break;
                    }
                }
                if (!foundPatient) {
                    printf("Patient with CCCD %s not found!\n", id);
                    system("pause");
                    break;
                }
// In lich su kham dang bang
                printf("\n=== VISIT HISTORY ===\n");
                printf("------------------------------------------------\n");
                printf("| %-4s | %-10s | %-11s | %-10s |\n", "No", "CCCD", "Visit Date", "Visit #");
                int printed = 0;
                for (int i = 0; i < recordCount; i++) {
                    if (strcmp(records[i].cardId, id) == 0) {
                        printf("| %-4d | %-10s | %-11s | %-10d |\n",
                               ++printed, records[i].cardId, records[i].visitDate, records[i].visitNumber);
                    }
                }
                if(printed==0) printf("No visit history for this patient.\n");
                printf("------------------------------------------------\n");
                system("pause");
            }
            break;

// ===== CASE 0: Thoat =====
        case 0:
            printf("\nExiting the program...\n");
            break;

        default:
            printf("\nInvalid choice!\n");
        } // end switch
    } while(choice != 0);
    return 0;
}

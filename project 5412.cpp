#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
// ===== Cau truc du lieu =====
struct Patient {
    char cardId[10];   // Ma ho so / CCCD
    char name[50];     // Ten benh nhan
    char phone[15];    // So dien thoai
    double debt;       // Tien vien phi
    int visitDays;     // So ngay kham
};
struct Record {
    char cardId[10];   // Ma ho so
    int visitNumber;   // So lan kham
};
// ===== Du lieu mau =====
struct Patient patients[MAX] = {
    {"BN001", "Nguyen Van A", "0901234567", 0, 2},
    {"BN002", "Tran Thi B",   "0912345678", 100000, 1},
    {"BN003", "Le Van C",     "0987654321", 0, 5}
};
int count = 3;
struct Record records[MAX] = {
    {"BN001", 1},
    {"BN001", 2},
    {"BN002", 1},
    {"BN003", 1},
    {"BN003", 2}
};
int recordCount = 5;
void swapPatients(struct Patient *a, struct Patient *b);
void themBenhNhan();
void CapnhatdanhSachBenhNhan();
void Xuatvien();
void Hienthidanhsachbenhnhan();
void Timkiembenhnhan();
void Sapxepdanhsachbenhnhan();
void Ghinhankhambenh();
void Xemlichsukhambenh();

void swapPatients(struct Patient *a, struct Patient *b){
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}
// ===== Ham chuc nang =====
void themBenhNhan() {
    printf("\n>>> Chuc nang: Them benh nhan\n");
}
void CapnhatdanhSachBenhNhan() {
    printf("\n>>> Chuc nang: Cap nhat thong tin benh nhan\n");
}
void Xuatvien() {
    printf("\n>>> Chuc nang: Xuat vien\n");
}
void Hienthidanhsachbenhnhan() {
    printf("\n>>> Chuc nang: Hien thi danh sach benh nhan\n");
}
void Timkiembenhnhan() {
    printf("\n>>> Chuc nang: Tim kiem benh nhan\n");
}
void Sapxepdanhsachbenhnhan() {
    printf("\n>>> Chuc nang: Sap xep danh sach benh nhan\n");
}
void Ghinhankhambenh() {
    printf("\n>>> Chuc nang: Ghi nhan kham benh\n");
}
void Xemlichsukhambenh() {
    printf("\n>>> Chuc nang: Xem lich su kham benh\n");
}
// ===== Main =====
int main() {
    int choice;
    struct Patient p;
    p.cardId[0]='\0'; p.name[0]='\0'; p.phone[0]='\0';
    p.debt=0; p.visitDays=0;
    char input[10];

    do {
        system("cls");
        printf("\n======================================================\n");
        printf("|                 HE THONG BENH VIEN                 |\n");
        printf("======================================================\n");
        printf("|  1 | Them benh nhan                                |\n");
        printf("|  2 | Cap nhat thong tin benh nhan                  |\n");
        printf("|  3 | Xuat vien                                     |\n");
        printf("|  4 | Hien thi danh sach benh nhan                  |\n");
        printf("|  5 | Tim kiem benh nhan                            |\n");
        printf("|  6 | Sap xep danh sach benh nhan                   |\n");
        printf("|  7 | Ghi nhan kham benh                            |\n");
        printf("|  8 | Xem lich su kham benh                         |\n");
        printf("|  0 | Thoat                                         |\n");
        printf("======================================================\n");
        printf("Nhap lua chon: ");
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")]=0;
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
                themBenhNhan();
                if(count>=MAX){
                    printf("Danh sach da day, khong the them benh nhan!\n");
                    system("pause");
                    break;
                }
                printf("\n=== THEM BENH NHAN ===\n");
                do{
                    printf("Nhap CCCD: ");
                    fgets(patients[count].cardId,sizeof(patients[count].cardId),stdin);
                    patients[count].cardId[strcspn(patients[count].cardId,"\n")]=0;
                }while(strlen(patients[count].cardId)==0);
                do{
                    printf("Nhap ten: ");
                    fgets(patients[count].name,sizeof(patients[count].name),stdin);
                    patients[count].name[strcspn(patients[count].name,"\n")]=0;
                }while(strlen(patients[count].name)==0);
                do{
                    printf("Nhap SDT (9 so): ");
                    fgets(patients[count].phone,sizeof(patients[count].phone),stdin);
                    patients[count].phone[strcspn(patients[count].phone,"\n")]=0;
                }while(strlen(patients[count].phone)!=9);
                patients[count].debt=0;
                patients[count].visitDays=0;
                count++;
                printf(">>> Da them benh nhan thanh cong!\n");
                system("pause");
                break;
// ===== CASE 2: Cap nhat danh sach =====
			case 2:
		    CapnhatdanhSachBenhNhan();
		    printf("\n=== CAP NHAT THONG TIN BENH NHAN ===\n");		
// Nhap CCCD de tim benh nhan can cap nhat
		    {
		        char id[10];
		        int foundIndex = -1;
		        do {
		            printf("Nhap ma ho so (CCCD): ");
		            fgets(id, sizeof(id), stdin);
		            id[strcspn(id, "\n")] = 0;
		        } while (strlen(id) == 0);		
// Tim benh nhan theo CCCD
		        for (int i = 0; i < count; i++) {
		            if (strcmp(patients[i].cardId, id) == 0) {
		                foundIndex = i;
		                break;
		            }
		        }		
		        if (foundIndex == -1) {
		            printf("Khong tim thay benh nhan voi CCCD %s\n", id);
		            system("pause");
		            break;
		        }		
// Nhap ten (bat buoc, khong de trong)
		        do {
		            printf("Nhap ten benh nhan: ");
		            fgets(patients[foundIndex].name, sizeof(patients[foundIndex].name), stdin);
		            patients[foundIndex].name[strcspn(patients[foundIndex].name, "\n")] = 0;
		        } while (strlen(patients[foundIndex].name) == 0);		
// Nhap SDT: 
		        while (1) {
		            char phoneBuf[15];
		            int valid = 1;
		            printf("Nhap so dien thoai (9 so): ");
		            fgets(phoneBuf, sizeof(phoneBuf), stdin);
		            phoneBuf[strcspn(phoneBuf, "\n")] = 0;
		            if (strlen(phoneBuf) != 9) {
		                printf("SDT phai co 9 ky tu. Thu lai.\n");
		                continue;
		            }
		            for (size_t k = 0; k < strlen(phoneBuf); k++) {
		                if (phoneBuf[k] < '0' || phoneBuf[k] > '9') {
		                    valid = 0; break;
		                }
		            }
		            if (!valid) {
		                printf("SDT chi duoc gom cac chu so. Thu lai.\n");
		                continue;
		            }
// Neu dung
		            strcpy(patients[foundIndex].phone, phoneBuf);
		            break;
		        }		
		        printf("\n>>> Da cap nhat thong tin benh nhan thanh cong!\n");
		        system("pause");
		    }
		    break;
// ===== CASE 3: Xuat vien =====
            case 3:
                Xuatvien();
                printf("\n=== XUAT VIEN ===\n");
                if(count==0){
                    printf("Chua co benh nhan nao trong he thong!\n");
                    system("pause");
                    break;
                }
                {
                    char id[10]; int found=0;
                    printf("Nhap ma ho so (CCCD): ");
                    fgets(id,sizeof(id),stdin); id[strcspn(id,"\n")]=0;
                    for(int i=0;i<count;i++){
                        if(strcmp(patients[i].cardId,id)==0){
                            found=1;
                            if(patients[i].debt>0){
                                printf("Khong the xuat vien! Benh nhan con no: %.2f\n",patients[i].debt);
                                system("pause");
                            } else {
                                for(int j=i;j<count-1;j++){
                                    patients[j]=patients[j+1];
                                }
                                count--;
                                printf(">>> Xuat vien thanh cong!\n");
                                system("pause");
                            }
                            break;
                        }
                    }
                    if(!found){
                        printf("Khong tim thay benh nhan!\n");
                        system("pause");
                    }
                }
                break;
// ===== CASE 4: Hien thi danh sach =====
            case 4:
                Hienthidanhsachbenhnhan();
                if(count==0){
                    printf("Chua co benh nhan nao!\n");
                    system("pause");
                    break;
                }
                {
                    int page=1; 
					char pageInput[10];
                    while(1){
                        printf("\nNhap trang (1-10) | 0 de thoat: ");
                        fgets(pageInput,sizeof(pageInput),stdin);
                        page=atoi(pageInput);
                        if(page==0) break;
                        if(page<1||page>10){
                            printf("Trang khong hop le!\n"); continue;
                        }
                        system("cls");
                        printf("\n================== TRANG %d ==================\n",page);
                        printf("| %-3s | %-10s | %-20s | %-10s | %-10s | %-5s |\n",
                               "STT","CCCD","Ten","SDT","CONG NO","Ngay");
                        printf("---------------------------------------------------------------\n");
                        int start=(page-1)*10; int end=start+10; if(end>count) end=count;
                        for(int i=start;i<end;i++){
                            printf("| %-3d | %-10s | %-20s | %-10s | %-10.2f | %-5d |\n",
                                   i+1,patients[i].cardId,patients[i].name,patients[i].phone,
                                   patients[i].debt,patients[i].visitDays);
                        }
                        printf("---------------------------------------------------------------\n");
                    }
                }
                break;
// ===== CASE 5: Tim kiem =====
            case 5:
                Timkiembenhnhan();
                if(count==0){
                    printf("Danh sach hien khong co benh nhan!\n");
                    system("pause");
                    break;
                }
                {
                    char keyword[50]; int found=0;
                    do{
                        printf("Nhap chuoi ten can tim: ");
                        fgets(keyword,sizeof(keyword),stdin);
                        keyword[strcspn(keyword,"\n")]=0;
                    }while(strlen(keyword)==0);
                    printf("\n=== KET QUA TIM KIEM ===\n");
                    printf("| %-3s | %-10s | %-20s | %-10s | %-10s | %-5s |\n",
                           "STT","CCCD","Ten","SDT","CONG NO","Ngay");
                    printf("---------------------------------------------------------------\n");
                    for(int i=0;i<count;i++){
                        if(strstr(patients[i].name,keyword)!=NULL){
                            printf("| %-3d | %-10s | %-20s | %-10s | %-10.2f | %-5d |\n",
                                   i+1,patients[i].cardId,patients[i].name,patients[i].phone,
                                   patients[i].debt,patients[i].visitDays);
                            found=1;
                        }
                    }
                    if(!found) printf("Khong tim thay benh nhan!\n");
                    printf("---------------------------------------------------------------\n");
                    system("pause");
                }
                break;
// ===== CASE 6: Sap xep =====
            case 6:
                Sapxepdanhsachbenhnhan();
                if(count<2){
                    printf("Khong co nhieu benh nhan de sap xep!\n");
                    system("pause");
                    break;
                }
                {
                    char sortInput[10]; int mode;
                    printf("Chon kieu sap xep: 1-Ten A->Z | 2-Cong no tang | 3-Cong no giam: ");
                    fgets(sortInput,sizeof(sortInput),stdin);
                    mode=atoi(sortInput);
                    if(mode==1){
                        for(int i=0;i<count-1;i++)
                            for(int j=i+1;j<count;j++)
                                if(strcmp(patients[i].name,patients[j].name)>0)
                                    swapPatients(&patients[i],&patients[j]);
                        printf(">>> Da sap xep danh sach theo ten A->Z!\n");
                    } else if(mode==2){
                        for(int i=0;i<count-1;i++)
                            for(int j=i+1;j<count;j++)
                                if(patients[i].debt>patients[j].debt)
                                    swapPatients(&patients[i],&patients[j]);
                        printf(">>> Da sap xep danh sach theo cong no tang dan!\n");
                    } else if(mode==3){
                        for(int i=0;i<count-1;i++)
                            for(int j=i+1;j<count;j++)
                                if(patients[i].debt<patients[j].debt)
                                    swapPatients(&patients[i],&patients[j]);
                        printf(">>> Da sap xep danh sach theo cong no giam dan!\n");
                    } else { printf("Lua chon khong hop le!\n"); }
                    system("pause");
                }
                break;
// ===== CASE 7: Ghi nhan kham =====
			case 7:
			    Ghinhankhambenh();
			    if (count == 0) {
			        printf("Danh sach hien khong co benh nhan!\n");
			        system("pause");
			        break;
			    }			
			    {
			        char id[10];
			        int found = -1;		
			        printf("Nhap ma ho so benh nhan (CCCD) de ghi nhan kham: ");
			        fgets(id, sizeof(id), stdin);
			        id[strcspn(id, "\n")] = 0;			
			        for (int i = 0; i < count; i++) {
			            if (strcmp(patients[i].cardId, id) == 0) {
			                found = i;
			                break;
			            }
			        }			
			        if (found == -1) {
			            printf("Khong tim thay benh nhan voi CCCD %s\n", id);
			            system("pause");
			            break;
			        }			
// Kiem tra xem benh nhan da co lich kham
			        int alreadyVisited = 0;
			        for (int i = 0; i < recordCount; i++) {
			            if (strcmp(records[i].cardId, id) == 0) {
			                alreadyVisited = 1;
			                break;
			            }
			        }			
			        if (alreadyVisited) {
			            printf("Benh nhan da co lich kham!\n");
			            system("pause");
			            break;
			        }			
			        patients[found].visitDays++;			
			        strcpy(records[recordCount].cardId, id);
			        records[recordCount].visitNumber = patients[found].visitDays;
			        recordCount++;			
			        printf(">>> Ghi nhan kham benh thanh cong! So lan kham: %d\n",
			               patients[found].visitDays);
			        system("pause");
			    }
			    break;
// ===== CASE 8: Xem lich su kham =====
			case 8:
			    Xemlichsukhambenh();
			    if (count == 0) {
			        printf("Danh sach hien khong co benh nhan!\n");
			        system("pause");
			        break;
			    }
			    {
			        char id[10];
			        int foundPatient = 0;
			        printf("Nhap ma ho so benh nhan (CCCD) de xem lich su kham: ");
			        fgets(id, sizeof(id), stdin);
			        id[strcspn(id, "\n")] = 0;
			
			        for (int i = 0; i < count; i++) {
			            if (strcmp(patients[i].cardId, id) == 0) {
			                foundPatient = 1;
			                break;
			            }
			        }
			        if (!foundPatient) {
			            printf("Khong tim thay benh nhan voi CCCD %s\n", id);
			            system("pause");
			            break;
			        }
			        // In lich su kham
			        int foundRecord = 0;
			        printf("\n=== LICH SU KHAM BENH ===\n");
			        printf("| %-3s | %-10s | %-5s | %-10s |\n", "STT", "CCCD", "Lan", "Trang thai");
			        printf("--------------------------------------\n");
			        for (int i = 0; i < recordCount; i++) {
			            if (strcmp(records[i].cardId, id) == 0) {
			                printf("| %-3d | %-10s | %-5d | %-10s |\n",
			                       i + 1,
			                       records[i].cardId,
			                       records[i].visitNumber,
			                       "Da kham");
			                foundRecord = 1;
			            }
			        }
			        if (!foundRecord) {
			            printf("Benh nhan chua co lich su kham nao.\n");
			        }
			        printf("--------------------------------------\n");
			        system("pause");
			    }
			    break;
// ===== CASE 0: Thoat =====
            case 0:
                printf("\nThoat chuong trinh...\n");
                break;

            default:
                printf("\nLua chon khong hop le!\n");
        }
    } while(choice!=0);
    return 0;
}


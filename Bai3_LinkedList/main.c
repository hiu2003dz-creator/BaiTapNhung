#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
typedef struct TaskNode{
    char task_de__description[50];
    struct TaskNode* next;
}TaskNode_t ; // kiểu dữ liệu struct này có 54 byte

TaskNode_t *head = NULL; // phải khai báo con trỏ trỏ vào null để tiết kiệm bộ nhớ và cho con trỏ phải cấp phát động
TaskNode_t *tail = NULL;

void queue_add_task(const char* description){
    TaskNode_t *newNode = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    strcpy(newNode -> task_de__description,description);// cop 
    newNode -> next = NULL; // trỏ đến cấu trúc next để đi tiếp sắp người (Hiện tại đang khai báo con trỏ chưa trỏ đến đâu)
    if(head == NULL){ // nếu như chưa có đầu thì sẽ sắp đầu và cuối tự thêm toa
        head = newNode;
        tail = newNode ;
    } else { // nếu có sẵn rồi thì sẽ sắp cuối lên 
        tail -> next = newNode;
        tail = newNode; // cập nhật lại toa sau 
    }
    printf("da them tac vu ",description);
}
TaskNode_t* queue_get_next_task(void){
    if(head = NULL){
        return NULL;
    }
    TaskNode_t * run_to_head = head ; // tạo ra đầu để ghi vị trí đầu lại
    head = head -> next ;
    if(head = NULL){
       tail = NULL;
}
    run_to_head = NULL ;
    return run_to_head;
}
void print_task_queue(void){
    if(head = NULL){
        printf("Danh sach trong");
        return;
    }
    TaskNode_t* dia_chi = head;
    while(dia_chi = ! NULL){
        printf("Danh sach cac cac vu");
        dia_chi = dia_chi -> next;
    }
}
typedef struct HistoryNode {
    char log_entry[50];         
    struct HistoryNode* next;   
    struct HistoryNode* prev;   
} HistoryNode_t;
HistoryNode_t* history_head = NULL; 
void history_log_activity(const char* entry){
    // Xin cấp phát động vì chưa biết HistoryNode_t có kích thước là bao nhiêu
    HistoryNode_t *newNode = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    strcpy(newNode->log_entry,entry);
    newNode->prev = NULL;
    newNode->next = history_head; // móc nối
    if(history_head = ! NULL){
        history_head -> prev = newNode;
    }
    history_head = newNode;
    printf("DA GHI NHAT KY %s", entry);
}
void history_navigate(void){
    if ( history_head = NULL ){
        printf("Khong co du lieu");
        return;
    }
    HistoryNode_t* current = history_head;
    char cmd;
    printf("----DOC NHAT KY ----");
    printf("Dang o trang: %s\n", current->log_entry);
    printf("Phim chuc nang: [n] Trang cu hon | [p] Trang moi hon | [q] Thoat\n");
    while (1){
        printf("mời nhập lệnh");
        scanf(" %c ", &cmd);
        if (cmd == "q"){
            printf("da thoat");
            break;
        }
        else if(cmd == "n"){
          if(current -> next != NULL){
            current = current -> prev;
            printf("Dang o trang: %s\n", current->log_entry);
          }else{
            printf("Da den cuoi so (khong con trang cu hon)!\n");
          }
        }else if(cmd == "q"){
              if(current ->prev =! NULL){
                current = current -> next;
                printf("Dang o trang: %s\n", current->log_entry);
              }else{
                printf("Da den dau trang (khong con trang cu hon)!\n");
              
        }
}else{
    printf("Khong co lenh nao hop le");
}        
}
} 
int main() {
    char input_buffer[100]; 
    char description[50];  

    printf("==========================================\n");
    printf("HE THONG ROBOT QUAN LY CONG VIEC \n");
    printf("Cac lenh: add <viec>, run, list, history, exit\n");
    printf("==========================================\n");

    
    while (1) {
        printf("\ngõ lệnh đi >> ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            break;
        }
        input_buffer[strcspn(input_buffer, "\n")] = 0;
        if (strlen(input_buffer) == 0) continue;

        // -----------------------------------------------------
        // 1. Lệnh EXIT (Thoát chương trình)
        // -----------------------------------------------------
        if (strcmp(input_buffer, "exit") == 0 || strcmp(input_buffer, "quit") == 0) {
            printf("Đóng cửa xưởng. Chào tạm biệt ông chủ!\n");
            break;
        }
        
        // -----------------------------------------------------
        // 2. Lệnh LIST (In danh sách chờ)
        // -----------------------------------------------------
        else if (strcmp(input_buffer, "list") == 0) {
            print_task_queue();
        }
        
        // -----------------------------------------------------
        // 3. Lệnh HISTORY (Lật sổ nhật ký)
        // -----------------------------------------------------
        else if (strcmp(input_buffer, "history") == 0) {
            history_navigate();
        }
        
        // -----------------------------------------------------
        // 4. Lệnh ADD (Thêm việc mới)
        // -----------------------------------------------------
        else if (strncmp(input_buffer, "add ", 4) == 0) {
            // Cắt lấy phần tên công việc (nằm sau chữ "add ")
            strcpy(description, input_buffer + 4); 
            
            // Gọi thợ đem việc cất vào cuối hàng đợi
            queue_add_task(description);
        }
        
        // -----------------------------------------------------
        // 5. Lệnh RUN (Thực thi việc đầu tiên) 
        // -----------------------------------------------------
        else if (strcmp(input_buffer, "run") == 0) {
            
            
            TaskNode_t* task_to_run = queue_get_next_task();
            
            if (task_to_run != NULL) {
             
                printf("🔥 ĐANG THỰC THI: %s\n", task_to_run->task_de__description);
                
                
                char log_message[100];
                sprintf(log_message, "Đã hoàn thành: %s", task_to_run->task_de__description);
                history_log_activity(log_message);
                
               
                free(task_to_run); 
                
            } 
            // Nếu task_to_run == NULL nghĩa là hàm queue_get_next_task đã báo xưởng rỗng (đã có printf ở trên)
        }
        
        // -----------------------------------------------------
        // Nếu gõ sai chính tả
        // -----------------------------------------------------
        else {
            printf("❌ Lệnh không hợp lệ! Vui lòng dùng: add, run, list, history, exit.\n");
        }
    }

    return 0;
}
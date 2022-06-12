#include "../project_function.h"
#include <errno.h>


static int reference_cnt_view1 = 0; // ONLY FOR MEMORY_LEAK_PURPOSE
static int reference_cnt_view2 = 0; //
static int reference_cnt_view3 = 0; //
void init_classroom(GtkWidget *button, gpointer data);


Classroom* generate_25p_coverage_pattern(Classroom *classroom, MyWidget *myWidget){

    const int NUMBER_OF_STUDENTS = myWidget->row * myWidget->col;

    for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
        classroom->students[i].hasSeat = false;
    }
    int tmp ;

    for(int z = myWidget->row ; z >= 0; z=z-2){
        for(int s = 0; s < myWidget->col ; s=s+2){
            tmp = z * myWidget->col + s;
            if (tmp >= myWidget->row * myWidget->col)
                continue;
            classroom->students[tmp].hasSeat = true;
           // g_print("%d actual value\n",z * myWidget->col + s);
        }
    }

    return classroom;
    
}


Classroom* generate_50p_coverage_pattern(Classroom *classroom, MyWidget *myWidget){

    //Users choice 50%
    bool first_element_row_state = true, temp_state;

    for(int i = 0; i < myWidget->row; i++){

        first_element_row_state = !first_element_row_state;
        
        temp_state = first_element_row_state;

        for(int j = 0; j < myWidget->col; j++){
            
            classroom->students[i * myWidget->col + j].hasSeat = !temp_state;

            temp_state = !temp_state;
        }
    }

    return classroom;
}


Classroom* generate_100p_coverage_pattern(Classroom *classroom, MyWidget *myWidget){
    
    //Users choice 100%
    for(int i = 0; i < myWidget->row; i++){

        for(int j = 0; j < myWidget->col; j++){
            
            classroom->students[i * myWidget->col + j].hasSeat = true;
        }
    }

    return classroom;
}

GtkWidget *create_view1(MyWidget *view) {
    GtkWidget *window = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *generate_button = gtk_button_new_with_label("generate");
    gtk_widget_set_name(generate_button, "generate_button");
    GtkWidget *row_input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *col_input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label_row = gtk_label_new("Number of rows");
    GtkWidget *label_col = gtk_label_new("Number of cols");
    GtkWidget *label_capacity = gtk_label_new("Capacity: ");
    GtkWidget *radio_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    view->row_entry_input = gtk_entry_new();
    view->col_entry_input = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(view->row_entry_input), "row");
    gtk_entry_set_placeholder_text(GTK_ENTRY(view->col_entry_input), "col");
    gtk_widget_set_name(view->row_entry_input, "row_entry_input");
    gtk_widget_set_name(view->col_entry_input, "col_entry_input");

    GtkWidget *radio_button = gtk_radio_button_new_with_label(NULL, "100 % ");
    GtkWidget *radio_button1 = gtk_radio_button_new_with_label(
            gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button)), "50 % ");
    GtkWidget *radio_button2 = gtk_radio_button_new_with_label(
            gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button)), "25 % ");


    g_signal_connect(generate_button, "clicked", G_CALLBACK(get_row_entry_input), view);
    g_signal_connect(generate_button, "clicked", G_CALLBACK(get_col_entry_input), view);
    g_signal_connect (generate_button, "clicked", G_CALLBACK(change_view), "2");
  //  g_signal_connect (generate_button, "clicked", G_CALLBACK(init_classroom), view);

    g_signal_connect (radio_button, "toggled", G_CALLBACK(radio_button_selected), (gpointer) "1");
    g_signal_connect (radio_button1, "toggled", G_CALLBACK(radio_button_selected), (gpointer) "2");
    g_signal_connect (radio_button2, "toggled", G_CALLBACK(radio_button_selected), (gpointer) "3");

    gtk_box_pack_start(GTK_BOX(radio_button_box), label_capacity, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(radio_button_box), radio_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(radio_button_box), radio_button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(radio_button_box), radio_button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row_input_box), label_row, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(row_input_box), view->row_entry_input, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(col_input_box), label_col, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(col_input_box), view->col_entry_input, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button_box, TRUE, false, 10);
    gtk_box_pack_start(GTK_BOX(vbox), row_input_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), col_input_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), generate_button, 0, 0, 10);

    gtk_box_set_homogeneous(GTK_BOX(col_input_box), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(row_input_box), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(radio_button_box), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_set_border_width(GTK_CONTAINER (window), 40);
    gtk_widget_set_size_request(window, 1400, 900);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    return window;
}
void free_classroom(Classroom *class){
    free(class->students);
    free(class);
}
GtkWidget *create_view2(MyWidget *view) {
    if (view->row <= 0 || view->row >= 200 || view->col >= 200 || view->col <= 0) {
        view->row = ROWS_DEFAULT; // default when user does not type anything or enters 0 or more then 200
        view->col = COLS_DEFAULT; // default when user does not type anything or enters 0
    }
    init_classroom(NULL,view);
    const int NUMBER_OF_STUDENTS = view->row * view->col;

    GtkWidget *window = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *option_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *return_button = gtk_button_new_with_label("back");
    GtkWidget *save_button = gtk_button_new_with_label("save");
    gtk_widget_set_name(return_button, "return_button");
    gtk_widget_set_name(save_button, "save_button");

    GtkWidget **hbox = malloc(view->row * (sizeof(GtkWidget)));
    GtkWidget **student_container = malloc(view->row * (sizeof(GtkWidget)));
    view->image = malloc(NUMBER_OF_STUDENTS * (sizeof(GtkWidget)));
    view->entry = malloc(NUMBER_OF_STUDENTS * (sizeof(GtkWidget)));

    if (hbox == NULL || student_container == NULL || view->image == NULL || view->entry == NULL) {
        perror("malloc hbox -> ");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < view->row; i++) {
        hbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_set_homogeneous(GTK_BOX(hbox[i]), TRUE);
    }
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        if (classroom->students[i].hasSeat == false) {
            view->image[i] = gtk_image_new_from_file("../resources/delete.png");
            gtk_widget_set_name(view->image[i], "delete_png");
        } else {
            view->entry[i] = gtk_entry_new();
            gtk_widget_set_name(view->entry[i], "entry");
            view->image[i] = gtk_image_new_from_file("../resources/icon.png");
            gtk_widget_set_name(view->image[i], "icon_png");
        }
    }
    int student_cnt = 0;
    for (int i = 0; i < view->row; i++) {
        for (int j = 0; j < view->col; j++) {
            student_container[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_box_set_homogeneous(GTK_BOX(student_container[i]), TRUE);
            gtk_box_pack_start(GTK_BOX(student_container[i]), view->image[student_cnt], 0, 0, 0);
           if (classroom->students[student_cnt].hasSeat == true) {
                gtk_box_pack_start(GTK_BOX(student_container[i]), view->entry[student_cnt], 0, 0, 0);
           }
            gtk_box_pack_start(GTK_BOX(hbox[i]), student_container[i], 0, 0, 0);
            if (classroom->students[student_cnt].hasSeat == true) {
                gtk_entry_set_width_chars(GTK_ENTRY(view->entry[student_cnt]), 8); // n_chars 8 e.g ic21b106 = 8 chars
                gtk_entry_set_max_length(GTK_ENTRY(view->entry[student_cnt]), 8); // n_chars 8 e.g ic21b106 = 8 chars
            }
            student_cnt++;
        }
    }
    for (int i = 0; i < view->row; i++)
        gtk_box_pack_start(GTK_BOX(vbox), hbox[i], 0, 0, 10);


    g_signal_connect (return_button, "clicked", G_CALLBACK(change_view), "1");
    g_signal_connect (return_button, "clicked", G_CALLBACK(free_classroom), classroom);
    g_signal_connect (save_button, "clicked", G_CALLBACK(get_student_name_entry_input), view);
    g_signal_connect (save_button, "clicked", G_CALLBACK(change_view), "3");


    gtk_box_pack_start(GTK_BOX(option_box), return_button, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(option_box), save_button, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(vbox), option_box, 1, 1, 5);

    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(option_box), TRUE);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_set_border_width(GTK_CONTAINER (window), 40);
    gtk_widget_set_size_request(window, 1400, 900);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);


    free(view->image);
    free(student_container);
    free(hbox);

    return window;
}

bool validate_user_input(StudentEntry *student_entry_input, Classroom *current_classroom) {
    for (int i = 0; i < current_classroom->number_of_students; ++i)
        if (strcmp(student_entry_input->name, current_classroom->students[i].name) == 0 &&
            strcmp("", current_classroom->students[i].name) != 0) {
            student_entry_input->found = true;
            student_entry_input->cell.row = current_classroom->students[i].cell.row;
            student_entry_input->cell.col = current_classroom->students[i].cell.col;
            return true;
        }
    student_entry_input->found = false;

    return false;
}

void get_student_entry_input(GtkWidget *button, gpointer data) {
    if (data == NULL)
        return;
    StudentEntry *student_entry_input = data;
    student_entry_input->name = gtk_entry_get_text(GTK_ENTRY(student_entry_input->entry));
    if (validate_user_input(student_entry_input, classroom) == false) {
        printf("no student with entered name found\n");
    }
    //create_view4(NULL,student_entry_input);
}

GtkWidget *create_view3(MyWidget *view) {
    const int NUMBER_OF_STUDENTS = view->row * view->col;


    GtkWidget **label_students_names = malloc(NUMBER_OF_STUDENTS * (sizeof(GtkWidget)));
    view->image = malloc(NUMBER_OF_STUDENTS * (sizeof(GtkWidget)));
    GtkWidget **student_container = malloc(view->row * (sizeof(GtkWidget)));
    GtkWidget **hbox = malloc(view->row * (sizeof(GtkWidget)));

    StudentEntry *student_entry_input = malloc(sizeof(StudentEntry));
    student_entry_input->entry = gtk_entry_new();

    GtkWidget *window = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *student_input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *input_button = gtk_button_new_with_label("Direkte / Indirekt Nachbar Abfragen");
    GtkWidget *student_label = gtk_label_new("Martikelnummer eingeben:");
    gtk_widget_set_name(input_button, "direct_indirect_button");
    gtk_widget_set_name(student_entry_input->entry, "direct_indirect_entry");
    //  g_signal_connect (input_button, "clicked", G_CALLBACK(get_direct_neighbour), "1");
    g_signal_connect (input_button, "clicked", G_CALLBACK(get_student_entry_input), student_entry_input);

    g_signal_connect (input_button, "clicked", G_CALLBACK(create_view4), student_entry_input);


    if (hbox == NULL || student_container == NULL || view->image == NULL || label_students_names == NULL) {
        perror("malloc -> ");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < view->row; i++) {
        hbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_set_homogeneous(GTK_BOX(hbox[i]), TRUE);
    }


    for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
        label_students_names[i] = gtk_label_new(classroom->students[i].name);
        gtk_widget_set_name(label_students_names[i], "students_names_label");
        if (classroom->students[i].hasSeat == true) {
            view->image[i] = gtk_image_new_from_file("../resources/icon.png");
            gtk_widget_set_name(view->image[i], "icon_png");
        } else
            view->image[i] = gtk_image_new_from_file("../resources/delete.png");
    }
int student_cnt = 0;
    for (int i = 0; i < view->row; i++) {
        for (int j = 0; j < view->col; j++) {
            student_container[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_box_set_homogeneous(GTK_BOX(student_container[i]), TRUE);
            gtk_box_pack_start(GTK_BOX(student_container[i]), view->image[student_cnt], 0, 0, 0);
            gtk_box_pack_start(GTK_BOX(student_container[i]), label_students_names[student_cnt], 0, 0, 0);
            gtk_box_pack_start(GTK_BOX(hbox[i]), student_container[i], 0, 0, 0);
            student_cnt++;
        }
    }
    for (int i = 0; i < view->row; i++)
        gtk_box_pack_start(GTK_BOX(vbox), hbox[i], 0, 0, 10);

    gtk_box_pack_start(GTK_BOX(student_input_box), student_label, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(student_input_box), student_entry_input->entry, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(student_input_box), input_button, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(vbox), student_input_box, 0, 0, 10);

    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(student_input_box), TRUE);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_set_border_width(GTK_CONTAINER (window), 40);
    gtk_widget_set_size_request(window, 1400, 900);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    free(label_students_names);
    free(view->image);
    free(student_container);
    free(hbox);

    return window;
}

void create_view4(MyWidget *view, StudentEntry *current_StudentEntry) {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    if (current_StudentEntry->found == false) {
        GtkWidget *alert_window = gtk_message_dialog_new(GTK_WINDOW(window),
                                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT |
                                                         GTK_DIALOG_USE_HEADER_BAR,
                                                         GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE,
                                                         "Wrong input! no student with entered name found.\n"
                                                         "Or no name was entered ! try again");
        gtk_widget_set_name(alert_window, "alert_window");
        gtk_dialog_run(GTK_DIALOG(alert_window));
        gtk_widget_destroy(alert_window);
    } else {
        int col = current_StudentEntry->cell.col;
        int row = current_StudentEntry->cell.row;
        GtkWidget *direct_neighbour;
        GtkWidget *indirect_neighbour;
        Student students_container_arr[widget->row][widget->col];

        char direct_neighbour_str[] = "Direct Neighbour of ";
        char *string_direct = malloc(
                4 + strlen(direct_neighbour_str) + strlen(current_StudentEntry->name) * sizeof(char));
        strcpy(string_direct, direct_neighbour_str);
        strcat(string_direct, current_StudentEntry->name);
        strcat(string_direct, " is:");

        char indirect_neighbour_str[] = "Indirect Neighbour of ";
        char *string_indirect = malloc(
                4 + strlen(indirect_neighbour_str) + strlen(current_StudentEntry->name) * sizeof(char));
        strcpy(string_indirect, indirect_neighbour_str);
        strcat(string_indirect, current_StudentEntry->name);
        strcat(string_indirect, " is:");

        GtkWidget *direct_neighbour_label = gtk_label_new(string_direct);
        GtkWidget *indirect_neighbour_label = gtk_label_new(string_indirect);
        gtk_widget_set_name(indirect_neighbour_label, "indirect_neighbour_label");
        gtk_widget_set_name(direct_neighbour_label, "direct_neighbour_label");

        free(string_direct);
        free(string_indirect);

        gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour_label, TRUE, TRUE, 0);

        int k = 0;
        for (int i = 0; i < widget->row; ++i)
            for (int j = 0; j < widget->col; ++j)
                students_container_arr[i][j] = classroom->students[k++];


        if (row - 1 >= 0)
            if (students_container_arr[row - 1][col].hasSeat == true) {
                direct_neighbour = gtk_label_new(students_container_arr[row - 1][col].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[0], students_container_arr[row - 1][col].name);
            }
        if (row + 1 <= widget->row - 1)
            if (students_container_arr[row + 1][col].hasSeat == true) {
                direct_neighbour = gtk_label_new(students_container_arr[row + 1][col].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[1], students_container_arr[row + 1][col].name);
            }

        if (col - 1 >= 0)
            if (students_container_arr[row][col - 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(students_container_arr[row][col - 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[2], students_container_arr[row][col - 1].name);

            }
        if (col + 1 <= widget->col - 1)
            if (students_container_arr[row][col + 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(students_container_arr[row][col + 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[3], students_container_arr[row][col + 1].name);

            }
        if (col + 1 <= widget->col - 1 && row - 1 >= 0)
            if (students_container_arr[row - 1][col + 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(
                        students_container_arr[row - 1][col + 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[4], students_container_arr[row - 1][col + 1].name);

            }
        if (col + 1 <= widget->col - 1 && row + 1 <= widget->row - 1)
            if (students_container_arr[row + 1][col + 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(
                        students_container_arr[row + 1][col + 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[5], students_container_arr[row + 1][col + 1].name);

            }
        if (col - 1 >= 0 && row - 1 >= 0)
            if (students_container_arr[row - 1][col - 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(
                        students_container_arr[row - 1][col - 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[6], students_container_arr[row - 1][col - 1].name);

            }
        if (col - 1 >= 0 && row + 1 <= widget->row - 1)
            if (students_container_arr[row + 1][col - 1].hasSeat == true) {
                direct_neighbour = gtk_label_new(
                        students_container_arr[row + 1][col - 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), direct_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[7], students_container_arr[row + 1][col - 1].name);
            }

        gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour_label, TRUE, TRUE, 0);

        if (row - 2 >= 0)
            if (students_container_arr[row - 2][col].hasSeat == true) {
                indirect_neighbour = gtk_label_new(students_container_arr[row - 2][col].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[8], students_container_arr[row - 2][col].name);

            }
        if (row + 2 <= widget->row - 1)
            if (students_container_arr[row + 2][col].hasSeat == true) {
                indirect_neighbour = gtk_label_new(students_container_arr[row + 2][col].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[9], students_container_arr[row + 2][col].name);

            }
        if (col - 2 >= 0)
            if (students_container_arr[row][col - 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(students_container_arr[row][col - 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[10], students_container_arr[row][col - 2].name);

            }
        if (col + 2 <= widget->col - 1)
            if (students_container_arr[row][col + 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(students_container_arr[row][col + 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[11], students_container_arr[row][col + 2].name);
            }

        if (col + 2 <= widget->col - 1 && row - 2 >= 0)
            if (students_container_arr[row - 2][col + 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 2][col + 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[12],
                       students_container_arr[row - 2][col + 2].name);
            }
        if (col + 2 <= widget->col - 1 && row + 2 <= widget->row - 1)
            if (students_container_arr[row + 2][col + 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 2][col + 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[13],
                       students_container_arr[row + 2][col + 2].name);
            }
        if (col - 2 >= 0 && row - 2 >= 0)
            if (students_container_arr[row - 2][col - 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 2][col - 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[14],
                       students_container_arr[row - 2][col - 2].name);
            }
        if (col - 2 >= 0 && row + 2 <= widget->row - 1)
            if (students_container_arr[row + 2][col - 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 2][col - 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[15],
                       students_container_arr[row + 2][col - 2].name);
            }


        if (col - 2 >= 0 && row + 1 <= widget->row - 1)
            if (students_container_arr[row + 1][col - 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 1][col - 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[16],
                       students_container_arr[row + 1][col - 2].name);

            }
        if (col - 2 >= 0 && row - 1 >= 0)
            if (students_container_arr[row - 1][col - 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 1][col - 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[17],
                       students_container_arr[row - 1][col - 2].name);

            }
        if (col + 2 <= widget->col - 1 && row + 1 <= widget->row - 1)
            if (students_container_arr[row + 1][col + 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 1][col + 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[18],
                       students_container_arr[row + 1][col + 2].name);

            }
        if (col + 2 <= widget->col - 1 && row - 1 >= 0)
            if (students_container_arr[row - 1][col + 2].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 1][col + 2].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[19],
                       students_container_arr[row - 1][col + 2].name);

            }

        if (col + 1 <= widget->col - 1 && row - 2 >= 0)
            if (students_container_arr[row - 2][col + 1].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 2][col + 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[20],
                       students_container_arr[row - 2][col + 1].name);

            }

        if (col + 1 <= widget->col - 1 && row + 2 <= widget->row - 1)
            if (students_container_arr[row + 2][col + 1].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 2][col + 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[21],
                       students_container_arr[row + 2][col + 1].name);
            }

        if (col - 1 >= 0 && row - 2 >= 0)
            if (students_container_arr[row - 2][col + 1].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row - 2][col - 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[22],
                       students_container_arr[row - 2][col - 1].name);

            }

        if (col - 1 >= 0 && row + 2 <= widget->row - 1)
            if (students_container_arr[row + 2][col + 1].hasSeat == true) {
                indirect_neighbour = gtk_label_new(
                        students_container_arr[row + 2][col - 1].name);
                gtk_box_pack_start(GTK_BOX(vbox), indirect_neighbour, TRUE, TRUE, 0);
                strcpy(current_StudentEntry->directIndirectNeighbour[23],
                       students_container_arr[row + 2][col - 1].name);

            }


        gtk_window_set_title(GTK_WINDOW(window), "Direct & Indirect Neighbour");
        gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
        gtk_container_set_border_width(GTK_CONTAINER(window), 15);
        gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);
        gtk_container_add(GTK_CONTAINER(window), vbox);
        gtk_widget_show_all(window);
    }
}

void change_view(GtkWidget *button, gpointer data) {
    if (strcmp((char *) data, "1") == 0) {
        gtk_container_remove(GTK_CONTAINER (widget->frame), widget->view2);
        g_object_ref (widget->view1);
        reference_cnt_view1++;
        //gtk_box_pack_start(GTK_BOX(widget->frame), widget->view1, 10, 10, 10);
        gtk_container_add(GTK_CONTAINER(widget->frame), widget->view1);
        g_object_unref(widget->view1); // ONLY FOR MEMORY_LEAK_PURPOSE
    }
    if (strcmp((char *) data, "2") == 0) {
        widget->view2 = create_view2(widget);
        gtk_container_remove(GTK_CONTAINER (widget->frame), widget->view1);
        g_object_ref (widget->view2);
        reference_cnt_view2++;
        //gtk_box_pack_start(GTK_BOX(widget->frame), widget->view2, 10, 10, 10);
        gtk_container_add(GTK_CONTAINER(widget->frame), widget->view2);
        g_object_unref(widget->view2);// ONLY FOR MEMORY_LEAK_PURPOSE
    }
    if (strcmp((char *) data, "3") == 0) {
        widget->view3 = create_view3(widget);
        gtk_container_remove(GTK_CONTAINER (widget->frame), widget->view2);
        g_object_ref (widget->view3);
        reference_cnt_view3++;
        //gtk_box_pack_start(GTK_BOX(widget->frame), widget->view3, 10, 10, 10);
        gtk_container_add(GTK_CONTAINER(widget->frame), widget->view3);
        g_object_unref(widget->view3);// ONLY FOR MEMORY_LEAK_PURPOSE
    }
}

//TODO: censor the seats when e.g 25 % capacity is selected
void radio_button_selected(GtkWidget *button, gpointer data) {
    if (strcmp((char *) data, "1") == 0) { // 100 %
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button))) {
            g_print("Index %s button 1 is active \n", (char *) data);
            widget->user_choice = 100;
        }
    } else if (strcmp((char *) data, "2") == 0) { // 50 %
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button))) {
            g_print("Index %s button 2 is active \n", (char *) data);
            widget->user_choice = 50;

        }
    } else if (strcmp((char *) data, "3") == 0) { // 25 %
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button))) {
            g_print("Index %s button 3 is active \n", (char *) data);
            widget->user_choice = 25;
        }
    }
}

gint convert_str_to_int(const gchar *tmp) {
    gchar *end_ptr; // for strTol.
    gdouble result;
    errno = 0;

    result = g_strtod(tmp, &end_ptr);
    if (end_ptr == tmp) {
        //fprintf(stderr, "no digits found\n");
        return -1;
    }
    return (gint) result;
}

void get_col_entry_input(GtkWidget *button, gpointer data) {
    if (data == NULL)
        return;
    MyWidget *myWidget = data;
    myWidget->col = convert_str_to_int(gtk_entry_get_text(GTK_ENTRY(myWidget->col_entry_input)));
}

void get_row_entry_input(GtkWidget *button, gpointer data) {
    if (data == NULL)
        return;
    MyWidget *myWidget = data;
    myWidget->row = convert_str_to_int(gtk_entry_get_text(GTK_ENTRY(myWidget->row_entry_input)));
}

void init_classroom(GtkWidget *button, gpointer data) {
    MyWidget *myWidget = data;
    if (myWidget->row <= 0 || myWidget->row >= 200 || myWidget->col >= 200 || myWidget->col <= 0) {
        myWidget->row = ROWS_DEFAULT; // default when user does not type anything or enters 0 or more then 200
        myWidget->col = COLS_DEFAULT; // default when user does not type anything or enters 0
    }
    const int NUMBER_OF_STUDENTS = myWidget->row * myWidget->col;
    classroom = malloc(sizeof(Classroom));
    classroom->students = (Student *) malloc(NUMBER_OF_STUDENTS * sizeof(Student));
    classroom->number_of_students = NUMBER_OF_STUDENTS;

    for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
        classroom->students[i].hasSeat = true;
    }
//    g_print("%d actual value\n",z * myWidget->col + s);

 //Generate Coverage Pattern depending on User's choice
    if(myWidget->user_choice == 25)(void)generate_25p_coverage_pattern(classroom, myWidget);

    if(myWidget->user_choice == 50)(void)generate_50p_coverage_pattern(classroom, myWidget);

    if(myWidget->user_choice == 100)(void)generate_100p_coverage_pattern(classroom, myWidget);


}

void get_student_name_entry_input(GtkWidget *button, gpointer data) {
    if (data == NULL)
        return;

    MyWidget *myWidget = data;
    const int NUMBER_OF_STUDENTS = myWidget->row * myWidget->col;
    int student_count = 0;

    for (int i = 0; i < myWidget->row; i++)
        for (int j = 0; j < myWidget->col; j++) {
            if (classroom->students[student_count].hasSeat  == true){
              //  g_print("%d student_count value\n",student_count);
                strcpy(classroom->students[student_count].name,gtk_entry_get_text(GTK_ENTRY(myWidget->entry[student_count])));
                if (strcmp(classroom->students[student_count].name, "") != 0) {
                    classroom->students[student_count].cell.row = i;
                    classroom->students[student_count].cell.col = j;
                    classroom->students[student_count].hasSeat = true;
                } else
                    classroom->students[student_count].hasSeat = false;
            } else {
                strcpy(classroom->students[student_count].name,"");
                classroom->students[student_count].hasSeat = false;
            }

            student_count++;


        }
}


/*
 *
 * #####################################################################################################################
 *                      functions below  ->   not used
void destroy (GtkWidget *window){
    g_object_ref_sink(window);
    g_object_unref(window);
    gtk_widget_destroy(window);
}
void display_pattern(int rows, int cols, GtkWidget *window, GtkWidget **entry, GtkWidget **hbox, GtkWidget *vbox) {
    const int NUMBER_OF_STUDENTS = rows * cols;
    if (rows * cols > MAX_SEATS_COUNT) {
        GtkWidget **entry_safe;
        entry_safe = (GtkWidget **) realloc(entry, NUMBER_OF_STUDENTS * sizeof(GtkWidget));
        if (entry_safe == NULL) { // reallocated pointer ptr1
            free(entry);
            exit(1);
        } else {
            entry = entry_safe;           // the reallocation succeeded, we can overwrite our original pointer now
        }
    }
    if (rows > ROWS_DEFAULT) {
        GtkWidget **hbox_safe;
        hbox_safe = (GtkWidget **) realloc(entry, NUMBER_OF_STUDENTS * sizeof(GtkWidget));
        if (hbox_safe == NULL) { // reallocated pointer ptr1
            free(entry);
            exit(1);
        } else {
            hbox = hbox_safe;           // the reallocation succeeded, we can overwrite our original pointer now
        }
    }

    for (int i = 0; i < NUMBER_OF_STUDENTS; i++)entry[i] = gtk_entry_new();
    GtkWidget *vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(vbox1), TRUE);

    for (int i = 0; i < rows; i++) {
        hbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_set_homogeneous(GTK_BOX(hbox[i]), TRUE);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gtk_box_pack_start(GTK_BOX(hbox[i]), entry[i * cols + j], 0, 0, 0);
            gtk_entry_set_width_chars(GTK_ENTRY(entry[i * cols + j]), 8); // n_chars 8 e.g ic21b106 = 8 chars
            gtk_entry_set_max_length(GTK_ENTRY(entry[i * cols + j]), 8);
        }
    }
    for (int i = 0; i < rows; i++)gtk_box_pack_start(GTK_BOX(vbox1), hbox[i], 0, 0, 10);
    remove_child_widget(window);
    //gtk_box_pack_start(GTK_BOX(vbox), vbox1, 0, 0, 10);
    //vbox = vbox1;
    gtk_container_add(GTK_CONTAINER(window), vbox1);

}

void remove_child_widget(GtkWidget *widget) {
    GList *children, *iter;
    int index = 0;

    children = gtk_container_get_children(GTK_CONTAINER(widget));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        // if (index == 2)
        //   break;
        gtk_widget_destroy(GTK_WIDGET(iter->data));
        //index++;
    }
    g_list_free(children);
}
*/

#include <gtest/gtest.h>

extern "C" {
#include"../project_function.h"
}
namespace {
    class PatternGenerator : public ::testing::Test {

    protected:
        PatternGenerator() {
        }

        ~PatternGenerator() override = default;

        void SetUp() override {
            widget_test = static_cast<MyWidget *>(malloc(sizeof(MyWidget)));
            widget_test->row_entry_input = gtk_entry_new();
            widget_test->col_entry_input = gtk_entry_new();
            gtk_entry_set_text(GTK_ENTRY(widget_test->row_entry_input), "5");
            gtk_entry_set_text(GTK_ENTRY(widget_test->col_entry_input), "5");
        }

        void TearDown() override {
            free(widget_test);
        }

        MyWidget *widget_test{};
    };

    TEST_F(PatternGenerator, case_1) {
        create_view2(widget_test);
        EXPECT_EQ(widget_test->col, 4);
        ASSERT_EQ(widget_test->row, 4);
    }

    TEST_F(PatternGenerator, case_2) {
        get_row_entry_input(nullptr, widget_test);
        get_col_entry_input(nullptr, widget_test);
        int expected = 5;
        EXPECT_EQ(widget_test->row, expected);
        EXPECT_EQ(widget_test->col, expected);
    }

    TEST_F(PatternGenerator, case_3) {
        get_row_entry_input(nullptr, widget_test);
        get_col_entry_input(nullptr, widget_test);
        create_view1(widget_test);
        int expected = 5;
        create_view2(widget_test);
        EXPECT_EQ(widget_test->row, expected);
        EXPECT_EQ(widget_test->col, expected);
    }

}
namespace {
    class inputOutput : public ::testing::Test {
    protected:
        inputOutput() {
        }

        ~inputOutput() override = default;

        void SetUp() override {
            widget_test = static_cast<MyWidget *>(malloc(sizeof(MyWidget)));
            widget_test->col, widget_test->row = 4;
            NUMBER_OF_STUDENTS = widget_test->col * widget_test->row;
            classroom = static_cast<Classroom *>(malloc(sizeof(Classroom)));
            classroom->students = (Student *) malloc(NUMBER_OF_STUDENTS * sizeof(Student));
            classroom->number_of_students = NUMBER_OF_STUDENTS;
            image = static_cast<GtkWidget **>(malloc(NUMBER_OF_STUDENTS * (sizeof(GtkWidget))));
            for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
                classroom->students[i].hasSeat = true;
            }
            for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
                if (classroom->students[i].hasSeat) {
                    image[i] = gtk_image_new_from_file("../resources/icon.png");
                }
            }
        }

        void TearDown() override {
            free(classroom->students);
            free(classroom);
            free(widget_test);
            free(image);
        }

    protected:
        GtkWidget **image;
        MyWidget *widget_test{};
        Classroom *classroom{};
        int NUMBER_OF_STUDENTS;
    };

    TEST_F(inputOutput, case_1) {
        create_view3(widget_test);
        for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
            ASSERT_NE(widget_test->image[i],nullptr);
        }
    }
    TEST_F(inputOutput, case_2) {
        create_view3(widget_test);
        for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
            ASSERT_NE(widget_test->image[i],image[i]);
        }
    }
    TEST_F(inputOutput, _25_Procent_Pattern) {

        //===== 1. SETUP Variables ====================================
        widget_test->user_choice = 25;
        widget_test->col = 4, widget_test->row = 4;
        NUMBER_OF_STUDENTS = widget_test->col * widget_test->row;

        //===== 2. Execute Function to be tested ======================
        classroom = generate_25p_coverage_pattern(classroom, widget_test);

        //===== 3. Test Values if Correct =============================
        int tmp ;

        for(int z = widget_test->row ; z >= 0; z=z-2){
            for(int s = 0; s < widget_test->col ; s=s+2){
                tmp = z * widget_test->col + s;
                if (tmp >= widget_test->row * widget_test->col)
                    continue;
                EXPECT_TRUE(classroom->students[tmp].hasSeat);
            }
        }

    }
    TEST_F(inputOutput, _50_Procent_Pattern) {

        //===== 1. SETUP Variables ====================================
        widget_test->user_choice = 50;
        widget_test->col = 4, widget_test->row = 4;
        NUMBER_OF_STUDENTS = widget_test->col * widget_test->row;

        //===== 2. Execute Function to be tested ======================
        classroom = generate_50p_coverage_pattern(classroom, widget_test);

        //===== 3. Test Values if Correct =============================
        bool first_element_row_state = true, temp_state;

        
        for(int i = 0; i < widget_test->row; i++){

            first_element_row_state = !first_element_row_state;
            
            temp_state = first_element_row_state;

            for(int j = 0; j < widget_test->col; j++){

                EXPECT_EQ(classroom->students[i * widget_test->col + j].hasSeat, !temp_state);
                temp_state = !temp_state;
            }
        }

    }
    
    TEST_F(inputOutput, _100_Procent_Pattern) {

        //===== 1. SETUP Variables ====================================
        widget_test->col = 4, widget_test->row = 4;
        NUMBER_OF_STUDENTS = widget_test->col * widget_test->row;

        //===== 2. Execute Function to be tested ======================
        classroom = generate_100p_coverage_pattern(classroom, widget_test);

        //===== 3. Test Values if Correct =============================
        for(int i = 0; i < widget_test->row; i++){

            for(int j = 0; j < widget_test->col; j++){
                
                EXPECT_TRUE(classroom->students[i * widget_test->col + j].hasSeat);
            }
        }
    }
}

namespace {
    class directIndirectNeigbour : public ::testing::Test {

    protected:
        directIndirectNeigbour() {
        }

        ~directIndirectNeigbour() override = default;

        void SetUp() override {
            widget_test = static_cast<MyWidget *>(malloc(sizeof(MyWidget)));
            widget = static_cast<MyWidget *>(malloc(sizeof(MyWidget)));
            widget_test->col, widget_test->row = 5;
            widget->row = 5;
            widget->col = 5;
            NUMBER_OF_STUDENTS = widget_test->col * widget_test->row;
            classroom = static_cast<Classroom *>(malloc(sizeof(Classroom)));
            classroom->students = (Student *) malloc(NUMBER_OF_STUDENTS * sizeof(Student));
            current_StudentEntry = static_cast<StudentEntry *>(malloc(sizeof(StudentEntry)));

            strcpy(classroom->students[0].name,"momo");
            classroom->students[0].hasSeat = true;

            strcpy(classroom->students[1].name,"yusuf");
            classroom->students[1].hasSeat = true;

            strcpy(classroom->students[2].name,"marwan");
            classroom->students[2].hasSeat = true;

            strcpy(classroom->students[3].name,"prince");
            classroom->students[3].hasSeat = true;

            strcpy(classroom->students[4].name,"Abdo");
            classroom->students[4].hasSeat = true;

            strcpy(classroom->students[5].name,"riad");
            classroom->students[5].hasSeat = true;

            strcpy(classroom->students[6].name,"umar");
            classroom->students[6].hasSeat = true;

            strcpy(classroom->students[7].name,"Baha");
            classroom->students[7].hasSeat = true;

            strcpy(classroom->students[8].name,"Amir");
            classroom->students[8].hasSeat = true;

            strcpy(classroom->students[9].name,"jamal");
            classroom->students[9].hasSeat = true;

            strcpy(classroom->students[10].name,"eskandar");
            classroom->students[10].hasSeat = true;

            strcpy(classroom->students[11].name,"jafer");
            classroom->students[11].hasSeat = true;

            strcpy(classroom->students[12].name,"wael");
            classroom->students[12].hasSeat = true;

            strcpy(classroom->students[13].name,"Ahmad");
            classroom->students[13].hasSeat = true;

            strcpy(classroom->students[14].name,"ali");
            classroom->students[14].hasSeat = true;

            strcpy(classroom->students[15].name,"ammar");
            classroom->students[15].hasSeat = true;

            strcpy(classroom->students[16].name,"bashr");
            classroom->students[16].hasSeat = true;

            strcpy(classroom->students[17].name,"nazir");
            classroom->students[17].hasSeat = true;

            strcpy(classroom->students[18].name,"munir");
            classroom->students[18].hasSeat = true;

            strcpy(classroom->students[19].name,"samer");
            classroom->students[19].hasSeat = true;

            strcpy(classroom->students[20].name,"teym");
            classroom->students[20].hasSeat = true;

            strcpy(classroom->students[21].name,"wafa");
            classroom->students[21].hasSeat = true;

            strcpy(classroom->students[22].name,"jawad");
            classroom->students[22].hasSeat = true;

            strcpy(classroom->students[23].name,"fadi");
            classroom->students[23].hasSeat = true;

            strcpy(classroom->students[24].name,"ghiyath");
            classroom->students[24].hasSeat = true;

        }

        void TearDown() override {
            free(widget_test);
            free(widget);
            free(classroom);
            free(current_StudentEntry);
        }

        MyWidget *widget_test{};
        int  NUMBER_OF_STUDENTS;
        StudentEntry *current_StudentEntry;
    };

    TEST_F(directIndirectNeigbour, case_1) {
        current_StudentEntry->found = true;
        current_StudentEntry->name = "wael";
        current_StudentEntry->cell.row = 2;
        current_StudentEntry->cell.col = 2;

        create_view4(widget_test,current_StudentEntry);
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[0],"Baha");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[1],"nazir");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[2],"jafer");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[3],"Ahmad");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[4],"Amir");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[5],"munir");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[6],"umar");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[7],"bashr");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[8],"marwan");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[9],"jawad");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[10],"eskandar");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[11],"ali");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[12],"Abdo");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[13],"ghiyath");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[14],"momo");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[15],"teym");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[16],"ammar");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[17],"riad");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[18],"samer");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[19],"jamal");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[20],"prince");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[21],"fadi");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[22],"yusuf");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[23],"wafa");
    }
    TEST_F(directIndirectNeigbour, case_2) {
        current_StudentEntry->found = true;
        current_StudentEntry->name = "momo";
        current_StudentEntry->cell.row = 0;
        current_StudentEntry->cell.col = 0;

        create_view4(widget_test, current_StudentEntry);
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[1],"riad");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[3],"yusuf");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[5],"umar");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[9],"eskandar");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[11],"marwan");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[13],"wael");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[18],"Baha");
        EXPECT_STREQ(current_StudentEntry->directIndirectNeighbour[21],"jafer");
    }
}
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
/*
 *
namespace {

    class MyTestFixture : public ::testing::Test {
    protected:
        MyTestFixture() : sbuf{nullptr} {
            // intentionally empty
        }

        ~MyTestFixture() override = default;

        // Called before each unit test
        void SetUp() override {
            // Save cout's buffer...
            sbuf = std::cout.rdbuf();
            // Redirect cout to our stringstream buffer or any other ostream
            std::cout.rdbuf(buffer.rdbuf());
        }

        // Called after each unit test
        void TearDown() override {
            // When done redirect cout to its old self
            std::cout.rdbuf(sbuf);
            sbuf = nullptr;
        }
        // The following objects can be reused in each unit test

        // This can be an ofstream as well or any other ostream
        std::stringstream buffer{};
        // Save cout's buffer here
        std::streambuf *sbuf;
    };
}

 */

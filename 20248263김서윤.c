#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    int age;
    int height;
} Student;

// 학생 정렬 함수
void sortStudents(Student* students, int n, int (*comparator)(const void*, const void*));

// 중복 학생 수를 세는 함수
int countSameStudents(Student* students, int n);

// 나이, 이름 순으로 비교하는 함수 선언
int compareByAgeThenName(const void* a, const void* b);

int main() {
    int n;

    // 학생 수 입력
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // 학생 메모리 할당
    Student* students = (Student*)malloc(n * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // 학생 정보 입력
    printf("Enter student details (name age height):\n");
    for (int i = 0; i < n; i++) {
        scanf("%49s %d %d", students[i].name, &students[i].age, &students[i].height);
    }

    // 나이, 이름 순으로 학생 정렬
    sortStudents(students, n, compareByAgeThenName);

    // 정렬된 학생 정보 출력
    printf("Sorted students:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d %d\n", students[i].name, students[i].age, students[i].height);
    }

    // 중복 학생 수 세기
    int sameStudentsCount = countSameStudents(students, n);
    printf("Number of duplicate pairs: %d\n", sameStudentsCount);

    // 할당된 메모리 해제
    free(students);

    return 0;
}

// qsort와 사용자 정의 비교 함수를 사용하여 학생 정렬
void sortStudents(Student* students, int n, int (*comparator)(const void*, const void*)) {
    qsort(students, n, sizeof(Student), comparator);
}

// 중복 학생 수를 세는 함수 정의
int countSameStudents(Student* students, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].age == students[j].age && students[i].height == students[j].height) {
                count++;
                break; // 중복된 학생을 찾으면 더 이상 비교하지 않음
            }
        }
    }
    return count;
}

// 나이, 이름 순으로 비교하는 함수 정의
int compareByAgeThenName(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    if (studentA->age != studentB->age) {
        return studentA->age - studentB->age;
    }
    return strcmp(studentA->name, studentB->name);
}
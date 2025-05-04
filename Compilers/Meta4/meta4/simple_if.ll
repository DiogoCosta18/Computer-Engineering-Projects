@.str_int = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str_float = private unnamed_addr constant [7 x i8] c"%.08F\0A\00"
@.str_true = private unnamed_addr constant [6 x i8] c"true\0A\00"
@.str_false = private unnamed_addr constant [7 x i8] c"false\0A\00"
@.str_string = private unnamed_addr constant [4 x i8] c"%s\0A\00"
@.empty_str = private unnamed_addr constant [1 x i8] c"\00"

declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)
@logic_result = global i1 false



define void @_main(i32 %argc, i8** %argv) {
  %trueBool = alloca i1
  %1 = load i1, i1* %trueBool
  %2 = xor i1 %1, 1
  store i1 %2, i1* %trueBool
  %3 = alloca i32
  %4 = load i1, i1* %trueBool
  %5 = icmp ne i1 %4, 0
  br i1 %5, label %L3then, label %L3else
L3then:
  %6 = alloca [9 x i8]
  store [9 x i8] c"trueBool\00", [9 x i8]* %6
  %ptr7 = getelementptr inbounds [9 x i8], [9 x i8]* %6, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr7)
  %8 = alloca i32
  %9 = load i1, i1* %trueBool
  %10 = xor i1 %9, 1
  %11 = icmp ne i1 %10, 0
  br i1 %11, label %L8then, label %L8else
L8then:
  %12 = alloca [16 x i8]
  store [16 x i8] c"Do not pressint\00", [16 x i8]* %12
  %ptr13 = getelementptr inbounds [16 x i8], [16 x i8]* %12, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr13)
  br label %L8end
L8else:
  %14 = alloca [16 x i8]
  store [16 x i8] c"or Not trueBool\00", [16 x i8]* %14
  %ptr15 = getelementptr inbounds [16 x i8], [16 x i8]* %14, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr15)
  %16 = alloca i32
  %17 = add i32 1, 0
  %18 = add i32 2, 0
  %19 = icmp ne i32 %17, %18
  %20 = icmp ne i1 %19, 0
  br i1 %20, label %L16then, label %L16else
L16then:
  %21 = alloca [19 x i8]
  store [19 x i8] c"one not equals two\00", [19 x i8]* %21
  %ptr22 = getelementptr inbounds [19 x i8], [19 x i8]* %21, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr22)
  %23 = alloca i32
  %24 = fadd double 11.012, 0.0
  %25 = fadd double 2.3, 0.0
  %26 = fcmp olt double %24, %25
  %27 = icmp ne i1 %26, 0
  br i1 %27, label %L23then, label %L23else
L23then:
  %28 = alloca [19 x i8]
  store [19 x i8] c"and for floats too\00", [19 x i8]* %28
  %ptr29 = getelementptr inbounds [19 x i8], [19 x i8]* %28, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr29)
  br label %L23end
L23else:
  br label %L23end
L23end:
  %30 = load i32, i32* %23
  br label %L16end
L16else:
  br label %L16end
L16end:
  %31 = load i32, i32* %16
  br label %L8end
L8end:
  %32 = load i32, i32* %8
  br label %L3end
L3else:
  %33 = alloca [17 x i8]
  store [17 x i8] c"Can't print this\00", [17 x i8]* %33
  %ptr34 = getelementptr inbounds [17 x i8], [17 x i8]* %33, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr34)
  br label %L3end
L3end:
  %35 = load i32, i32* %3
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main(i32 %argc, i8** %argv)
  ret i32 0
}

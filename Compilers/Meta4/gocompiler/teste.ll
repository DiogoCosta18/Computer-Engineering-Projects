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
  %i = alloca i32
  %counter = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %i
  %2 = add i32 0, 0
  store i32 %2, i32* %counter
  %3 = alloca i32
  store i32 0, i32* %3
  br label %L3for_cond
L3for_cond:
  %4 = load i32, i32* %i
  %5 = add i32 14, 0
  %6 = icmp slt i32 %4, %5
  %7 = icmp ne i1 %6, 0
  br i1 %7, label %L3body, label %L3end
L3body:
  %8 = alloca i32
  %9 = load i32, i32* %i
  %10 = add i32 0, 0
  %11 = icmp eq i32 %9, %10
  %12 = icmp ne i1 %11, 0
  br i1 %12, label %L8then, label %L8else
L8then:
  %13 = add i32 1, 0
  store i32 %13, i32* %counter
  br label %L8end
L8else:
  %14 = load i32, i32* %counter
  %15 = add i32 2, 0
  %16 = mul i32 %14, %15
  store i32 %16, i32* %counter
  br label %L8end
L8end:
  %17 = load i32, i32* %8
  %18 = alloca [18 x i8]
  store [18 x i8] c"2 to the power of\00", [18 x i8]* %18
  %ptr19 = getelementptr inbounds [18 x i8], [18 x i8]* %18, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr19)
  %20 = load i32, i32* %i
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %20)
  %22 = alloca [3 x i8]
  store [3 x i8] c"is\00", [3 x i8]* %22
  %ptr23 = getelementptr inbounds [3 x i8], [3 x i8]* %22, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr23)
  %24 = load i32, i32* %counter
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %24)
  %26 = alloca [1 x i8]
  store [1 x i8] c"\00", [1 x i8]* %26
  %ptr27 = getelementptr inbounds [1 x i8], [1 x i8]* %26, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr27)
  %28 = load i32, i32* %i
  %29 = add i32 1, 0
  %30 = add i32 %28, %29
  store i32 %30, i32* %i
  br label %L3for_cond
L3end:
  %31 = load i32, i32* %3
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
  call void @_main(i32 %argc, i8** %argv)
  ret i32 0
}

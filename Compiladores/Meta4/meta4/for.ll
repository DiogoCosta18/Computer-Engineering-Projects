define void @_main(i32 %argc, i8** %argv) {
  %i = alloca i32
  %counter = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %i
  %2 = add i32 1, 0
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
  %8 = load i32, i32* %i
  %9 = add i32 1, 0
  %10 = add i32 %8, %9
  store i32 %10, i32* %i
  %11 = load i32, i32* %counter
  %12 = add i32 2, 0
  %13 = mul i32 %11, %12
  store i32 %13, i32* %counter
  %14 = alloca [18 x i8]
  store [18 x i8] c"2 to the power of\00", [18 x i8]* %14
  %ptr15 = getelementptr inbounds [18 x i8], [18 x i8]* %14, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr15)
  %16 = load i32, i32* %i
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %16)
  %18 = alloca [3 x i8]
  store [3 x i8] c"is\00", [3 x i8]* %18
  %ptr19 = getelementptr inbounds [3 x i8], [3 x i8]* %18, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr19)
  %20 = load i32, i32* %counter
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %20)
  %22 = alloca [1 x i8]
  store [1 x i8] c"\00", [1 x i8]* %22
  %ptr23 = getelementptr inbounds [1 x i8], [1 x i8]* %22, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr23)
  br label %L3for_cond
L3end:
  %24 = load i32, i32* %3
  ret void
}


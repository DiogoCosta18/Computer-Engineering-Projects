@b = global i1 0
@a = global i32 0
define void @_main(i32 %argc, i8** %argv) {
@a = global i32 0
  %f = alloca double
  %1 = add i32 10, 0
  store i32 %1, i32* @a
  %2 = fadd double 10.12332, 0.0
  store double %2, double* %f
  %3 = load double, double* %f
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_float, i32 0, i32 0), double %3)
  %5 = load i32, i32* @a
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %5)
  %7 = fadd double 1.000003, 0.0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_float, i32 0, i32 0), double %7)
  %9 = fadd double 1.478347, 0.0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_float, i32 0, i32 0), double %9)
  %11 = add i32 0, 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %11)
  %13 = add i32 0, 0
  %14 = sub i32 0, %13
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %14)
  %16 = fadd double 0.00, 0.0
  %17 = fsub double -0.0, %16
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_float, i32 0, i32 0), double %17)
  %19 = alloca [10 x i8]
  store [10 x i8] c"sdjfhighi\00", [10 x i8]* %19
  %ptr20 = getelementptr inbounds [10 x i8], [10 x i8]* %19, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr20)
  %21 = alloca [6 x i8]
  store [6 x i8] c"\09 tab\00", [6 x i8]* %21
  %ptr22 = getelementptr inbounds [6 x i8], [6 x i8]* %21, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr22)
  %23 = alloca [10 x i8]
  store [10 x i8] c"\0A newline\00", [10 x i8]* %23
  %ptr24 = getelementptr inbounds [10 x i8], [10 x i8]* %23, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr24)
  %25 = alloca [10 x i8]
  store [10 x i8] c"\5C barra \5C\00", [10 x i8]* %25
  %ptr26 = getelementptr inbounds [10 x i8], [10 x i8]* %25, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr26)
  %27 = alloca [7 x i8]
  store [7 x i8] c"\0C feed\00", [7 x i8]* %27
  %ptr28 = getelementptr inbounds [7 x i8], [7 x i8]* %27, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr28)
  %29 = alloca [11 x i8]
  store [11 x i8] c"\0D carriage\00", [11 x i8]* %29
  %ptr30 = getelementptr inbounds [11 x i8], [11 x i8]* %29, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr30)
  %31 = alloca [10 x i8]
  store [10 x i8] c"\22aspazita\00", [10 x i8]* %31
  %ptr32 = getelementptr inbounds [10 x i8], [10 x i8]* %31, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr32)
  %33 = alloca [18 x i8]
  store [18 x i8] c"\0C varios \09  \5C \0A \22\00", [18 x i8]* %33
  %ptr34 = getelementptr inbounds [18 x i8], [18 x i8]* %33, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr34)
  %35 = alloca [27 x i8]
  store [27 x i8] c"cena do printf %s %d %l %x\00", [27 x i8]* %35
  %ptr36 = getelementptr inbounds [27 x i8], [27 x i8]* %35, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr36)
  %37 = alloca [1019 x i8]
  store [1019 x i8] c"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis quis blandit tellus. Curabitur ornare elementum mollis. Pellentesque eleifend tempor justo in facilisis. Phasellus ut mattis ex. Etiam et imperdiet nisl. Nam sit amet justo ante. Proin semper varius luctus. Quisque a lorem neque. Ut nec augue eu sapien interdum euismod at nec urna. Nulla et nunc sodales, pulvinar erat in, sagittis quam. Duis vulputate augue finibus ligula mattis congue. Maecenas condimentum nunc ante, non facilisis est aliquam sed. Donec vel ex nec est pharetra aliquam a quis dui. Aenean ac quam hendrerit, suscipit orci et, vestibulum quam. Donec volutpat hendrerit mi sed placerat. Donec dignissim sapien feugiat felis placerat cursus. Suspendisse mattis magna non risus ornare, a auctor nisl consequat. Nam viverra risus ac dui pharetra, id posuere massa mattis. Nullam at pellentesque neque. Curabitur tempus molestie mi ac ornare. Aenean tortor nisl, condimentum eget ligula a, consequat bibendum justo. Donec nec viverra massa. \00", [1019 x i8]* %37
  %ptr38 = getelementptr inbounds [1019 x i8], [1019 x i8]* %37, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %ptr38)
  ret void
}


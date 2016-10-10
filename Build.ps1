New-Item build -ItemType Directory -Force | out-null
Set-Location build | out-null
cmake .. -G "Visual Studio 14 2015 Win64"
Set-Location .. | out-null
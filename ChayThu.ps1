param([string]$Compiler = 'g++')
$ErrorActionPreference = 'Stop'
Set-Location -LiteralPath $PSScriptRoot

# Tim MinGW di kem Code::Blocks neu g++ chua co trong PATH.
$compilerCommand = Get-Command $Compiler -ErrorAction SilentlyContinue
if (-not $compilerCommand -and $Compiler -eq 'g++') {
    $codeBlocksCompiler = 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe'
    if (Test-Path -LiteralPath $codeBlocksCompiler) {
        $Compiler = $codeBlocksCompiler
        $compilerCommand = Get-Command $Compiler
    }
}
if (-not $compilerCommand) { throw "Khong tim thay compiler: $Compiler" }
$Compiler = $compilerCommand.Source
$env:Path = "$(Split-Path -Parent $Compiler);$env:Path"

New-Item -ItemType Directory -Path KetQua -Force | Out-Null
$compilerVersion = (& $Compiler --version | Select-Object -First 1)
$benchmarkStarted = (Get-Date).ToString('o')

# Bien dich 5 chuong trinh cua bai va chuong trinh kiem tra ket qua.
foreach ($ten in @('SinhTest','QuickSort','HeapSort','MergeSort','Sort','KiemTra')) {
    & $Compiler -std=c++17 -O2 "$ten.cpp" -o "$ten.exe"
    if ($LASTEXITCODE -ne 0) { throw "Khong bien dich duoc $ten.cpp" }
}

# Tao 10 test, moi test gom 1 trieu so thuc.
New-Item -ItemType Directory -Path DuLieu -Force | Out-Null
Push-Location -LiteralPath DuLieu
try {
    & '../SinhTest.exe'
    if ($LASTEXITCODE -ne 0) { throw 'Khong sinh duoc du lieu' }
} finally { Pop-Location }

# Chay moi thuat toan tren tung test va lay thoi gian o dong dau file OUT.
'Test,Loai,QuickSort_ms,HeapSort_ms,MergeSort_ms,Sort_ms' | Set-Content KetQua.csv -Encoding UTF8
'Kiem tra ket qua thuc te; khong nam trong khoang do thoi gian.' | Set-Content KetQua/KiemTra.txt -Encoding UTF8
for ($test = 1; $test -le 10; $test++) {
    Copy-Item -LiteralPath "DuLieu/TEST$test.IN" -Destination TEST.IN -Force
    $loai = if ($test -eq 1) { 'Tang dan' } elseif ($test -eq 2) { 'Giam dan' } else { 'Ngau nhien' }
    $dong = "$test,$loai"
    $cacFile = @('QUICKSORT.OUT','HEAPSORT.OUT','MERGESORT.OUT','SORT.OUT')
    $cacChuongTrinh = @('QuickSort','HeapSort','MergeSort','Sort')
    for ($i = 0; $i -lt 4; $i++) {
        & "./$($cacChuongTrinh[$i]).exe"
        if ($LASTEXITCODE -ne 0) { throw "Loi chay $($cacChuongTrinh[$i]), test $test" }
        $dau = Get-Content -LiteralPath $cacFile[$i] -TotalCount 1
        $thoiGian = ($dau -split ' ')[1]
        $dong += ",$thoiGian"
    }

    $kiemTra = & './KiemTra.exe' 'TEST.IN' @cacFile
    if ($LASTEXITCODE -ne 0) { throw "Ket qua sap xep sai o test $test" }
    "TEST $test" | Add-Content KetQua/KiemTra.txt -Encoding UTF8
    $kiemTra | Add-Content KetQua/KiemTra.txt -Encoding UTF8
    $dong | Add-Content KetQua.csv -Encoding UTF8
    Write-Host "Da chay xong test $test."
}
Write-Host 'Da chay xong 40 lan. Xem bang thoi gian trong KetQua.csv.'
$environment = [ordered]@{
    started = $benchmarkStarted
    finished = (Get-Date).ToString('o')
    compiler = $compilerVersion
    flags = '-std=c++17 -O2'
    cpu = (Get-ItemProperty 'HKLM:\HARDWARE\DESCRIPTION\System\CentralProcessor\0').ProcessorNameString.Trim()
    logical_processors = [Environment]::ProcessorCount
    os_version = [Environment]::OSVersion.VersionString
    seed = 20261009
    values_per_dataset = 1000000
    datasets = 10
    repetitions_per_algorithm_per_dataset = 1
    timing_scope = 'Sorting call only; excludes input, output and verification. MergeSort buffer is global.'
}
$environment | ConvertTo-Json | Set-Content KetQua/MoiTruong.json -Encoding UTF8
Get-ChildItem -LiteralPath DuLieu -Filter 'TEST*.IN' |
    Sort-Object Name | ForEach-Object {
        $hash = Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256
        "$($hash.Hash.ToLower())  $($_.Name)"
    } | Set-Content KetQua/SHA256.txt -Encoding UTF8

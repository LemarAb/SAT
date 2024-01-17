param (
    [char]$type,
    [int]$start,
    [int]$end
)

for ($test = $start; $test -le $end; $test++) {

    for ($heur = 0; $heur -le 3; $heur++) {
        & ./main $type$test $heur
        Start-Sleep -Milliseconds 1000
    }
    #Write-Host "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    Add-Content -Path "results.txt" -Value "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" 
}

# .\runAll.ps1 -type 'c' -start 1 -end 10

# Set-ExecutionPolicy -Scope Process Bypass

# param (
#     [char]$type,
#     [int]$start,
#     [int]$end
# )

# $skipList = @(25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
# 35, 36, 37, 38, 39, 40, 42, 43, 44, 77,
# 78, 79
# )

# for ($heur = 0; $heur -le 3; $heur++) {
#     for ($test = $start; $test -le $end; $test++) {
#         & ./main $type$test $heur
#     }
#     Add-Content -Path "results.txt" -Value "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" 
# }
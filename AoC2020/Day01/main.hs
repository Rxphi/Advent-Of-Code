import System.IO

main = do
    input <- readFile "input.txt"
    putStrLn "2020 Solution of Day 1"
    putStrLn $ "Part I: " ++ part1 input
    putStrLn $ "Part II: " ++ part2 input

part1 :: String -> String 
part1 input = let
    nums = map read (lines input)
    in (show . head) [a * b | a <- nums, b <- nums, a + b == 2020]

part2 :: String -> String
part2 input = let
    nums = map read (lines input)
    in (show . head) [a * b * c | a <- nums, b <- nums, c <- nums, a + b + c == 2020]
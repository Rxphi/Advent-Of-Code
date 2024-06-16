import System.IO

-- Custom types
data Policy = Policy Int Int Char
data InputLine = InputLine Policy String

main = do
    input <- readFile "input.txt"
    putStrLn "2020 Solution of Day 2"
    transformedInput <- transformInput input
    putStrLn $ "Part I: " ++ part1 transformedInput
    putStrLn $ "Part II: " ++ part2 transformedInput

-- Transform input into custom types
transformInput :: String -> IO [InputLine]
transformInput input = return $ map stringToInputLine (lines input)

stringToInputLine :: String -> InputLine
stringToInputLine string = let
    splitted = words string
    numbers = head splitted
    num1 = read $ takeWhile (/='-') numbers
    num2 = read $ tail $ dropWhile (/='-') numbers
    char = head $ splitted !! 1
    password = last splitted
    in InputLine (Policy num1 num2 char) password

-- Solving logic 
part1 :: [InputLine] -> String
part1 inputLines = (show . length) $ filter isValid1 inputLines

part2 :: [InputLine] -> String
part2 inputLines = (show . length) $ filter isValid2 inputLines

isValid1 :: InputLine -> Bool
isValid1 (InputLine (Policy min max char) password) = let 
    count = length [c | c <- password, c == char]
    in min <= count && count <= max

isValid2 :: InputLine -> Bool
isValid2 (InputLine (Policy ind1 ind2 char) password) = let 
    c1 = password !! (ind1 - 1)
    c2 = password !! (ind2 - 1)
    in (c1 == char && c2 /= char) || (c1 /= char && c2 == char)
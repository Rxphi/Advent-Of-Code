import System.IO 

type Forest = [[Bool]]
data Direction = Direction Int Int

main = do
    input <- readFile "input.txt"
    forest <- processInput input
    putStrLn "2020 Solution of Day 3"
    putStrLn $ "Part I: " ++ (part1 forest)
    putStrLn $ "Part II: " ++ (part2 forest)

processInput :: String -> IO Forest
processInput input = return [[x == '#' | x <- row] | row <- lines input]

part1 :: Forest -> String
part1 forest = show $ numOfTreesHit forest (Direction 3 1) 0 0 (length (head forest))

part2 :: Forest -> String
part2 forest = let
    len = length $ head forest
    in show $ foldr (*) 1 [numOfTreesHit forest (Direction x y) 0 0 len | (x, y) <- [(1,1), (3,1), (5,1), (7,1), (1,2)]]

-- Parameter: Forest -> current xcoord -> accumulated solution -> length of row -> solution
numOfTreesHit :: Forest -> Direction -> Int -> Int -> Int -> Int
numOfTreesHit [] _ _ solution _ = solution 
numOfTreesHit (row:rows) (Direction x y) xcoord acc len = let 
    inc = if row !! xcoord then 1 else 0
    remainingRows = drop (y-1) rows
    in numOfTreesHit remainingRows (Direction x y) ((xcoord + x) `mod` len) (acc + inc) len
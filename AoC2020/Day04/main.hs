import System.IO 
-- import Text.Megaparsec
-- import Text.Megaparsec.Char
import Text.Parsec
import Text.Parsec.Char
import Data.Void

-- byr (Birth Year)
-- iyr (Issue Year)
-- eyr (Expiration Year)
-- hgt (Height)
-- hcl (Hair Color)
-- ecl (Eye Color)
-- pid (Passport ID)
-- cid (Country ID)

type Parser = Parsec Void String
data FT = Byr | Iyr | Eyr | Hgt | Hcl | Ecl | Pid | Cid deriving (Show, Eq, Bounded, Enum, Ord)

-- main = do
--     input <- readFile "input.txt"
--     parsedInput <- parse p "" input

pFT :: Parser FT
pFT = let
    -- f :: FT -> Parser FT
    f x = try (string (show x)) >> return x
    in choice (map f [minBound :: FT .. maxBound :: FT])

-- pTuple :: Parser (FT, String)
-- pTuple = do
--     ft <- pFT
--     char ':' 
--     s <- manyTill anyChar space
--     return (ft, s)
        

-- p :: Parser [[(FT, String)]]
-- p = many1 
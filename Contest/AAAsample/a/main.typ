#import "../../../lib.typ": *

#let problem-id = "a"
#let title = "两数之和"
#let contest-id = "AAAsample"

#let statement = include problem-id + ".prob.typ"
#let solution = include problem-id + ".sol.typ"

#let content_ = title_ => make-problem(
  contest-id: contest-id,
  problem-id: problem-id,
  title: title_,
  statement: statement,
  solution: solution,
)
#let content = content_(upper(problem-id) + "." + title)

#show: article

#content_(contest-id + " " + upper(problem-id) + "." + title)()

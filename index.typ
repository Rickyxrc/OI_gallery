#import "lib.typ": *
#import "Contest/AAAsample/main.typ" as contest_abc123
#import "Contest/abc480/main.typ" as contest_abc480
#import "Contest/abc481/main.typ" as contest_abc481
#import "Contest/abc482/main.typ" as contest_abc482
#import "Contest/ICPC2026_Wuhan/main.typ" as contest_icpc2026_wuhan
#import "Contest/NOIP2023/main.typ" as contest_noip2023
#import "Contest/Collection-26.11/main.typ" as contest_collection_26_11
#import "Contest/CF1132/main.typ" as contest_cf1132
#import "Contest/abc483/main.typ" as contest_abc483

#show: article
#set document(title: "算法竞赛题解集")
#outline(title: outline-title, depth: 2)

#contest_abc480.contest()
#contest_abc481.contest()
#contest_abc482.contest()
#contest_icpc2026_wuhan.contest()
#contest_noip2023.contest()
#contest_collection_26_11.contest()
#contest_cf1132.contest()
#contest_abc483.contest()

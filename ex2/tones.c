#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


#define C[84] = {0.500000000000000, 0.537328768505032, 0.574449185136640, 0.611154060944930, 0.647238526336160, 0.682501174559806, 0.716745185867628, 0.749779426070224, 0.781419513359436, 0.811488847442084, 0.839819595240905, 0.866253627660945, 0.890643402192837, 0.912852786426657, 0.932757817879901, 0.950247395898571, 0.965223901769501, 0.977603743582735, 0.987317822802809, 0.994311919944721, 0.998546997201953, 0.999999416337403, 0.998661070621062, 0.994539430078020, 0.987657499794248, 0.978053691512884, 0.965781609237689, 0.950909750040368, 0.933521121741672, 0.913712779600253, 0.891595284595211, 0.867292086325991, 0.840938833973973, 0.812682619171648, 0.782681155005349, 0.751101895733945, 0.718121102136829, 0.683922857707998, 0.648698041187358, 0.612643261164129, 0.575959758698881, 0.538852284089265, 0.501527954048811, 0.464195095677493, 0.427062083676471, 0.390336177297151, 0.354222363516166, 0.318922212893143, 0.284632754497322, 0.251545376182672, 0.219844756349649, 0.189707833156017, 0.161302816930112, 0.134788251298802, 0.110312128270490, 0.0880110622123612, 0.0680095273323418, 0.0504191629218018, 0.0353381502368046, 0.0228506644958716 0.0130264050529505, 0.00592020636794743, 0.00157173194620253, 5.25295519826496e-06, 0.00122951275415939, 0.00523767809267645, 0.0120073772507406, 0.0215008249073090, 0.0336650330404428, 0.0484321066818710, 0.0657196228752144, 0.0854310907227026, 0.107456489952614, 0.131672885001409, 0.157945111183026, 0.186126529115478, 0.216059843193871, 0.247577979541520, 0.280505018538844, 0.314657176725093, 0.349843832592392, 0.385868590546591, 0.422530377096385, 0.459624563152291};


#define C1[79]={0.500000000000000,0.539535613293140,0.578823652115549,0.617618092323238,0.655676000717460,0.692759056307519,0.728635042691641,0.763079302210538,0.795876142767646,0.826820188506460,0.855717665886923,0.882387617107399,0.906663033273681,0.928391900219084,0.947438150426615,0.963682515092233,0.977023270993518,0.987376877486827,0.994678499643996,0.998882414252699,0.999962296138048,0.997911383012477,0.992742517821605,0.984488068320915,0.973199724386851,0.958948174331600,0.941822662248476,0.921930429159860,0.899396041467241,0.874360610908658,0.846980910908216,0.817428394851148,0.785888122432048,0.752557600799547,0.717645547754254,0.681370584744907,0.643959867847251,0.605647665298555,0.566673890495337,0.527282599640741,0.487720463449407,0.448235222480104,0.409074135768938,0.370482432477876,0.332701776254477,0.295968751919090,0.260513383955990,0.226557696085739,0.194314320938831,0.163985168536932,0.135760161919758,0.109816047835178,0.0863152899400855,0.0654050514428636,0.0472162735582202,0.0318628555451513,0.0194409414626930,0.0100283181098420,0.00368392791977834,0.000447499858681810,0.000339300640472884,0.00336000781538925,0.00949070552712394,0.0186930029650944,0.0309092747700880,0.0460630218878469,0.0640593506109065,0.0847855668088969,0.108111881626200,0.133892224227840,0.161965156504143,0.192154884006224,0.224272356781768,0.258116453217593,0.293475239475710,0.330127296636205,0.367843107236291,0.406386492522947,0.445516091418966};

#define D[75]={ 0.500000000000000,0.541876867904127,0.583459465673031,0.624455591017461,0.664577162809279,0.703542245437075,0.741077029977027,0.776917758257265,0.810812576295260,0.842523304084087,0.871827109291212,0.898518073108651,0.922408637251249,0.943330921934950,0.961137905573585,0.975704457904421,0.986928219282657,0.994730319966026,0.999055934335088,0.999874666154666,0.997180762169195,0.990993152531043,0.981355317777700,0.968334983292609,0.952023643396650,0.932535918414531,0.910008749233968,0.884600435017548,0.856489520829275,0.825873542992503,0.792967640995664,0.758003045699965,0.721225454472489,0.682893304662666,0.643275957554482,0.602651805555823,0.561306315925830,0.519530024787024,0.477616495518372,0.435860255875717,0.394554728335499,0.353990168205314,0.314451623990271,0.276216934347724,0.239554775705838,0.204722774265451,0.171965695652237,0.141513724940571,0.113580849135392,0.0883633534784504,0.0660384421454248,0.0467629930263191,0.0306724553393447,0.0178798978247847,0.00847521420721914,0.00252449150934991,6.95456563072350e-05,0.00112762763376156,0.00569130226467685,0.0137285004565456,0.0251827445519616,0.0399735451989862,0.0579969669524854,0.0791263586319386,0.103213243303471,0.130088361632178,0.159562861273066,0.191429623942723,0.225464720846347,0.261428986232788,0.299069698020188,0.338122353682405,0.378312528917011,0.419357806033934,0.460969758513908};

#define Eb[71]={ 0.500000000000000,0.544373660211635,0.588397138741776,0.631723017422453,0.674009383304041,0.714922526914794,0.754139575781346,0.791351042427348,0.826263266742301,0.858600733446264,0.888108246361781,0.914552942334447,0.937726128908915,0.957444931258057,0.973553735368273,0.985925416091822,0.994462340374817,0.999097137743739,0.999793231970071,0.996545129717327,0.989378463892577,0.978349791360348,0.963546146615284,0.945084354935812,0.923110110439183,0.897796826313550,0.869344266300669,0.837976968229076,0.803942472038686,0.767509366280634,0.728965168508700,0.688614056289559,0.646774466737924,0.603776583520238,0.559959731158617,0.515669697198298,0.471256003371129,0.427069147290145,0.383457836442816,0.340766236311366,0.299331254337019,0.259479881162224,0.221526610132846,0.185770955424722,0.152495088380693,0.121961610711301,0.0944114821323137,0.0700621187934265,0.0491056775047080,0.0317075393010696,0.0180050043119563,0.00810620823589570,0.00208926897071615,1.67013393481685e-06,0.00185988633836165,0.00764925318011511,0.0173240829650596,0.0308080252603909,0.0479946694260219,0.0687483843707948,0.0929053889064568,0.120275044252528,0.150641358492064,0.183764691105656,0.219383644132082,0.257217125031209,0.296966564969752,0.338318275023927,0.380945921704670,0.424513102269418,0.468675999496978};

#define E[67]={ 0.500000000000000,0.546997289985896,0.593578438615265,0.639330989289335,0.683849822297845,0.726740741984734,0.767623967185886,0.806137494032577,0.841940301344408,0.874715370229297,0.904172491153245,0.930050833624444,0.952121255738248,0.970188333132948,0.984092089390801,0.993709412562340,0.998955145271212,0.999782838747159,0.996185164110451,0.988193977266058,0.975880036832929,0.959352377605996,0.938757345098648,0.914277299714389,0.886129002021689,0.854561693429773,0.819854889260125,0.782315903755166,0.742277128939103,0.700093091425505,0.656137313232341,0.610799004400658,0.564479616702366,0.517589288952619,0.470543215402055,0.423757969365272,0.377647814638269,0.332621037365703,0.289076330837759,0.247399265227727,0.207958873529302,0.171104383923687,0.137162127510042,0.106432648780012,0.0791880444218926,0.0556695540182008,0.0360854239700162,0.0206090635621522,0.00937750949643024,0.00249021248897086,8.15667567494183e-06,0.00195331962319428,0.00830847772676607,0.0190173587180328,0.0339851399324552,0.0530792879243682,0.0761307319952390,0.102935361244026,0.133255831883882,0.166823668822172,0.203341642895186,0.242486402708132,0.283911337776570,0.327249647617354,0.372117589613575,0.418117876895025,0.464843196147349};

#define F[63]={ 0.500000000000000,0.549775916629212,0.599057297342699,0.647354519560107,0.694187738556642,0.739091654837865,0.781620137004061,0.821350654174903,0.857888473937169,0.890870584107891,0.919969299349252,0.944895516802622,0.965401588396231,0.981283781289374,0.992384302008059,0.998592864161789,0.999847784165851,0.996136594082830,0.987496165494616,0.974012343174213,0.955819092196908,0.933097166964455,0.906072315365852,0.875013035916800,0.840227910161233,0.802062536838141,0.760896098273507,0.717137593111081,0.671221772810741,0.623604822286321,0.574759827596831,0.525172075720656,0.475334233110644,0.425741450932298,0.376886445615747,0.329254603597409,0.283319158886928,0.239536491371460,0.198341592569773,0.160143743885039,0.125322450293906,0.0942236698716663,0.0671563766140902,0.0443894907051504,0.0261492067291695,0.0126167463722566,0.00392655794049696,0.000164980583120866,0.00136938649192270,0.00752780959938731,0.0185790644644998,0.0344133541650787,0.0548733611570741,0.0797558102628750,0.108813488259956,0.141757700004757,0.178261136689597,0.217961127735798,0.260463244014661,0.305345216597401,0.352161132100320,0.400445862943423,0.449719688506776};

#define F1[59]={ 0.500000000000000,0.552712748582119,0.604837982401445,0.655794734894734,0.705015062914284,0.751950376790256,0.796077554687037,0.836904773105529,0.873976988546960,0.906881009241843,0.935250100416646,0.958768071769770,0.977172801599493,0.990259158305375,0.997881286701285,0.999954233657727,0.996454894954712,0.987422272791962,0.972957041086318,0.953220423401396,0.928432396015599,0.898869236156378,0.864860442727117,0.826785063846949,0.785067472135266,0.740172634827850,0.692600931442005,0.642882576750859,0.591571711226091,0.539240224814599,0.486471382886766,0.433853325398903,0.381972511725546,0.331407184222836,0.282720923375427,0.236456366358621,0.193129159026079,0.153222208731774,0.117180302041890,0.0854051473254484,0.0582508974769198,0.0360202026727363,0.0189608371560540,0.00726293764625308,0.00105688415273442,0.000411846812593875,0.00533501494852995,0.0157715169395899,0.0316050317978422,0.0526590856345913,0.0786990185662517,0.109434600137555,0.144523264111643,0.183573926573411,0.226151344791068,0.271780968253829,0.319954227818060,0.370134204011201,0.421761611316882};

#define G[56]= { 0.500000000000000,0.555839320381912,0.610980020974150,0.664732222595041,0.716423417922968,0.765406885404715,0.811069780551565,0.852840803390935,0.890197346144093,0.922672031703608,0.949858561105949,0.971416796840075,0.987077018393426,0.996643296793138,0.999995945922729,0.997093019945218,0.987970838098054,0.972743530293991,0.951601609213029,0.924809586750332,0.892702664641341,0.855682540668505,0.814212382919235,0.768811034973402,0.720046524520741,0.668528956623472,0.614902880538334,0.559839225598625,0.504026907048470,0.448164206850830,0.392950037306140,0.339075196784623,0.287213726974045,0.238014479774528,0.192092999349137,0.150023820895953,0.112333282493623,0.0794929399531985,0.0519136670647182,0.0299405150518164,0.0138483955490322,0.00383864111316518,3.64863009909566e-05,0.00248950082820487,0.0111669944127378,0.0259604007485985,0.0466846358062493,0.0730804134654778,0.104817489509297,0.141498793392455,0.182665396090948,0.227802251878537,0.276344642193441,0.327685240974381,0.381181713069769,0.436164750654437};

#define Ab[53]={ 0.500000000000000,0.559162911530560,0.617494563239343,0.674175374798930,0.728408960769586,0.779433320096226,0.826531542492611,0.869041881284305,0.906367051183390,0.937982620357907,0.963444378884483,0.982394580054796,0.994566966843288,0.999790512912501,0.997991825593578,0.989196177079208,0.973527149340381,0.951204897756009,0.922543057852026,0.887944338611374,0.847894864270432,0.802957344101640,0.753763166149303,0.701003526004360,0.645419715261990,0.587792706112641,0.528932178406674,0.469665143366235,0.410824323785222,0.353236453979657,0.297710663878286,0.245027110461040,0.195926016277675,0.151097269059271,0.111170728551727,0.0767073767636664,0.0481914359709035,0.0260235652222914,0.0105152309384460,0.00188433069843069,0.000252131701740321,0.00564156692127965,0.0179769128869867,0.0370848536273558,0.0626969158201077,0.0944532409372741,0.131907641384732,0.174533869595631,0.221733011994745,0.272841903945924,0.327142447449672,0.383871700673892,0.442232597556338};  

#define A[50]={  0.500000000000000,0.562686451042781,0.624383670923355,0.684118039162140,0.740946910298537,0.793973489422225,0.842360984154279,0.885345809751045,0.922249638946024,0.952490106375772,0.975589998667326,0.991184785161855,0.999028370435040,0.998996977835840,0.991091102758986,0.975435504827335,0.952277239107485,0.921981757427249,0.885027141318659,0.841996557594222,0.793569055612137,0.740508851455329,0.683653268126648,0.623899522071412,0.562190564544209,0.499500201251980,0.436817725094660,0.375132304508295,0.315417373772267,0.258615271611301,0.205622370504647,0.157274931371186,0.114335906852330,0.0774829014450993,0.0472974784819754,0.0242559827000232,0.00872202322485532,0.000940735592615150,0.00103491335884570,0.00900307033985665,0.0247194640656270,0.0479360800741407,0.0782865457337588,0.115291911831078,0.158368210687223,0.206835671530802,0.259929447703217,0.316811686414345,0.376584750580364,0.438305384094890}


#define Bb[47]={ 0.500000000000000,0.566346247039256,0.631519128047792,0.694366028550602,0.753775470182642,0.808696767730716,0.858158611018562,0.901286243005342,0.937316930294413,0.965613452448823,0.985675371548339,0.997147882680356,0.999828088839391,0.993668589260476,0.978778317725017,0.955420616013262,0.924008576575307,0.885097736787825,0.839376254002149,0.787652735142844,0.730841936096298,0.669948583802679,0.606049607165527,0.540275091034096,0.473788290096628,0.407765056148708,0.343373042575566,0.281751053827315,0.223988905101788,0.171108148426425,0.124044006007918,0.0836288303672184,0.0505773837755729,0.0254741973319881,0.00876323324307271,0.000740033132920925,0.00154649124404133,0.0111683449678462,0.0294354270859035,0.0560246752609410,0.0904658455532751,0.132149828916309,0.180339423589794,0.234182372875764,0.292726437717672,0.354936237516748,0.419711561347434};


#define B[45]={ 0.500000000000000,0.570319134690903,0.639240472260726,0.705394000867607,0.767464726914960,0.824218814370051,0.874528110840179,0.917392572879436,0.951960144757922,0.977543695545102,0.993634677833582,0.999913236596461,0.996254567235363,0.982731396434459,0.959612536506309,0.927357541966084,0.886607574550301,0.838172658264351,0.783015577801785,0.722232740401068,0.657032381565998,0.588710547874417,0.518625334286691,0.448169888062293,0.378744715910098,0.311729844848234,0.248457390157292,0.190185075718538,0.138071233097331,0.0931517763376146,0.0563196101603471,0.0283068808877496,0.00967042290782966,0.000780689972982696,0.00181439135527423,0.0127509792362111,0.0333730571543379,0.0632707013915749,0.101849609398188,0.148342913282770,0.201826423539790,0.261237000001338,0.325393684837022,0.393021177522233,0.462775185141583};


#define c[42]= {  0.500000000000000,0.574477426576656,0.647293112464023,0.716822393738826,0.781513932752840,0.839924331585735,0.890750337146210,0.932857919361046,0.965307573659392,0.987375283203136,0.998568673153968,0.998637996543079,0.987581706626686,0.965646491396993,0.933321769478554,0.891328770217640,0.840604441609698,0.782280545111308,0.717658403773280,0.648179867114672,0.575395140569598,0.500928197296343,0.426440544080682,0.353594149788718,0.284014363509796,0.219253649760027,0.160756949886768,0.109829442530537,0.0676074224730921,0.0350329476229616,0.0128328198149936,0.00150236840442486,0.00129439847599572,0.0122135502557196,0.0340161955781388,0.0662158737190888,0.108094145309646,0.158716622158678,0.216953815326527,0.281506336287497,0.350933888892707,0.423687405264483}; 

#define c1[]= { 0.500000000000000,0.578827177464168,0.655682785789557,0.728644567318457,0.795887654011693,0.855730209746428,0.906675495201685,0.947449303234689,0.977031828441078,0.994683173800305,0.999961856452172,0.992735849751242,0.973185885423127,0.941800933231472,0.899365971214991,0.846942352376648,0.785841258879370,0.717590907692988,0.643898327921406,0.566606665808198,0.487649085277397,0.409000417016274,0.332627765418744,0.260441308773312,0.194246523246172,0.135699025599102,0.0862631640838988,0.0471753932083552,0.0194133484180242,0.00367139417575718,0.000343257013018627,0.00951217792270920,0.0309488303948235,0.0641170561675497,0.108187275235295,0.162057234712086,0.224379577594559,0.293595541894322,0.367973947281008,0.445654494129931};


#define d[40]={ 0.500000000000000,0.583508743952514,0.664671549142057,0.741208379229993,0.810969151386669,0.871994136704771,0.922569013164932,0.961273024598341,0.987018892758352,0.999083361285881,0.997127513523416,0.981206293406924,0.951766961973481,0.909636532844617,0.855998539649460,0.792359788040315,0.720508026307490,0.642461723716105,0.560413367398521,0.476667870713668,0.393577823313821,0.313477401882602,0.238616798132539,0.171099006119641,0.112820744654135,0.0654191744229095,0.0302259066533391,0.00822959531324324,4.81637118795453e-05,0.00591144571600050,0.0256547292262418,0.0587233832913660,0.104188438874853,0.160772685576859,0.226886551198966,0.300672756218195,0.380058488730855};


#define eb[35]={ 0.500000000000000,0.588448439106623,0.674107106746891,0.754274224243389,0.826421223096880,0.888272499115616,0.937877187742373,0.973670696698011,0.994524055127036,0.999779522713050,0.989271335609207,0.963330934831782,0.922776512206947,0.868887203604322,0.803362743434145,0.728269852954330,0.645977053365510,0.559079959768393,0.470319412303010,0.382495026713384,0.298376891058080,0.220618193759918,0.151671538812532,0.0937115876640539,0.0485664677471299,0.0176601111137155,0.00196734188434727,0.00198312910841009,0.0177069748376340,0.0486429298319893,0.0938152364025958,0.151799104997337,0.220765653798191,0.298539593880661,0.382667840475140};

#define e[33]={  0.500000000000000,0.593641562222881,0.683969332424480,0.767786787211884,0.842127790541171,0.904361559479645,0.952285762476370,0.984204455574975,0.998988098558392,0.996113527171337,0.975682466881658,0.938417933014675,0.885638644652749,0.819212357742180,0.741489768857676,0.655221328641077,0.563459908724297,0.469452766563997,0.376526631341529,0.287969977513738,0.206916652123750,0.136234974073981,0.0784262299215136,0.0355361582314164,0.00908255488390597,1.56124213579467e-06,0.00861453593747691,0.0346166826151123,0.0770878360818182,0.134525025155230,0.204895659878943,0.285709460911770,0.374106585650546};

#define f[32]= { 0.500000000000000,0.599060796570539,0.694194318040130,0.781628986518553,0.857898445905689,0.919978985922763,0.965409417406122,0.992388646395623,0.999847078683252,0.987489023981535,0.955804418594302,0.906049401843348,0.840196516300489,0.760856506141739,0.671174813935630,0.574706879260733,0.475277182951089,0.376827625174375,0.283261248408958,0.198287500937896,0.125275175403993,0.0671188526915001,0.0261241459799842,0.00391629448124742,0.00137573066964836,0.0186031754493700,0.0549156450641877,0.108873528056196,0.178337658804780,0.260554124959723,0.352263446569354,0.449829798486378};

#define f1[30]={ 0.500000000000000,0.604837982401445,0.705015062914284,0.796077554687037,0.873976988546960,0.935250100416646,0.977172801599493,0.997881286701285,0.996454894954712,0.972957041086318,0.928432396015599,0.864860442727117,0.785067472135266,0.692600931442005,0.591571711226091,0.486471382886766,0.381972511725546,0.282720923375427,0.193129159026079,0.117180302041890,0.0582508974769198,0.0189608371560540,0.00105688415273442,0.00533501494852995,0.0316050317978422,0.0786990185662517,0.144523264111643,0.226151344791068,0.319954227818060,0.421761611316882};

#define g[28]={ 0.500000000000000,0.610980020974150,0.716423417922968,0.811069780551565,0.890197346144093,0.949858561105949,0.987077018393426,0.999995945922729,0.987970838098054,0.951601609213029,0.892702664641341,0.814212382919235,0.720046524520741,0.614902880538334,0.504026907048470,0.392950037306140,0.287213726974045,0.192092999349137,0.112333282493623,0.0519136670647182,0.0138483955490322,3.64863009909566e-05,0.0111669944127378,0.0466846358062493,0.104817489509297,0.182665396090948,0.276344642193441,0.381181713069769};

#define ab[26]={ 0.500000000000000,0.617495257244172,0.728410231057680,0.826533164629941,0.906368715177782,0.963445718819617,0.994567596645407,0.997991378072410,0.973525315342268,0.922539622291460,0.847889735973808,0.753756398842738,0.645411517638362,0.528922911975773,0.410814488093242,0.297700869618353,0.195916947736423,0.111163097682819,0.0481859310933944,0.0105124635731906,0.000252585341723011,0.0179808975217146,0.0627045317912620,0.131918755649278,0.221747249139523,0.327159196881194};

#define a[25]= { 0.500000000000000,0.624383670923355,0.740946910298537,0.842360984154279,0.922249638946024,0.975589998667326,0.999028370435040,0.991091102758986,0.952277239107485,0.885027141318659,0.793569055612137,0.683653268126648,0.562190564544209,0.436817725094660,0.315417373772267,0.205622370504647,0.114335906852330,0.0472974784819754,0.00872202322485532,0.00103491335884570,0.0247194640656270,0.0782865457337588,0.158368210687223,0.259929447703217,0.376584750580364};

#define b[22]={ 0.500000000000000,0.639241843767776,0.767467139930006,0.874530948997363,0.951962587750594,0.993635813449599,0.996253520408565,0.959608600673802,0.886600330007794,0.783004982751838,0.657018824079365,0.518609637216299,0.378728091550968,0.248441346676067,0.138057439949101,0.0563097343480265,0.00966595154349453,0.00181645816571052,0.0333822910749736,0.101866022116472,0.201849349845688,0.325421785146098};

#define bb[24]={ 0.500000000000000,0.631638295977244,0.753988297184181,0.858417083634106,0.937556242177551,0.985821775946669,0.999808106788341,0.978528370183788,0.923484047633894,0.838559023303823,0.729745540206882,0.604721392244042,0.472308185096724,0.341848890658751,0.222548614277853,0.122825089752382,0.0497147306461125,0.00837614647385870,0.00172615526588032,0.0302339751786499,0.0918881168302750,0.182338312411382,0.295202467164876,0.422516974979255};


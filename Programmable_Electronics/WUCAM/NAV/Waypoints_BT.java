
import java.util.TreeMap;

public class Waypoints_BT {

// BT stands for "Bordeaux-Toulon"
// 242 waypoints known by WUCAM firmware 58c56a6, see also
// https://jl-noullet.github.io/Programmable_Electronics/WUCAM/NAV/beacons_bordeaux_toulon.html
public final String names[] = {
"AB","ABILI","ABLAK","ADC","ADIMA","ADITA","AFRIC","AG","AGN","AGREV",
"ALM","AMFOU","AMIKO","AMLIR","AMOLO","AMONI","AMVAR","ANETO","AR","ARBON",
"ASKAN","ASPET","AUB","AUCHE","AULON","AVN","BADAM","BADET","BARAT","BASLI",
"BEGUY","BELPA","BGC","BIDAC","BIRGO","BISBI","BLEU","BMC","BODRU","BOLSA",
"BORGO","BRIVE","BRUSC","BTZ","BUGUS","BZ","CALAN","CHALA","CIRC","CL",
"CM","CS","CUERS","CVU","DA","DEGOL","DEPES","DGN","DIRAX","DIVKO",
"DONOS","ENSAC","ERGUL","ESERA","ESPAL","ESPIG","ETPAR","ETREK","EVALA","FINOT",
"FISTO","FJR","GAI","GALDO","GANGU","GAUDE","GIGNA","GILON","GILUR","GIROL",
"GIROM","GOMET","GONIM","GONUP","JAUN","JULEE","KELAM","KINES","KONON","KORAB",
"KOTIT","KUBOL","KURIR","LABAP","LACOU","LACX","LANET","LAPOS","LAPRO","LASUR",
"LATAM","LATEK","LEKLA","LERGA","LFCM","LFMX","LFNB","LIBRU","LOGIS","LOMRA",
"LUC","LUKUM","LULUT","LUMID","LUNEL","LURAN","LUSOL","MAGEC","MAKOX","MALEB",
"MALOU","MAPRI","MARRE","MARRI","MASAM","MAXIR","MAZET","MEBEL","MEDAP","MEDOK",
"MEDUS","MEIZE","MEN","MEZIN","MIL","MINDI","MINPA","MIRBA","MOKDI","MOLEN",
"MONIX","MORIL","MOTIM","MRM","MTG","MTL","MURRO","NAKIS","NARAK","NEDRU",
"NEKTA","NELEN","NETRO","NG","NIVET","NORON","OB","OBUTO","OGALO","OGREN",
"OKTET","OLRAK","ORBIL","ORG","ORTEZ","OSKIL","OSMAS","OVDIL","OXIDO","PADKO",
"PALME","PERDU","PERIG","PERUS","PIMAK","PINED","PIPOR","POKET","POMEG","PPG",
"PPGX","PU","PX","RATRA","RETNO","RH","RHONE","RIBOU","RIKPO","RILON",
"ROBEX","ROCAN","ROLIR","ROMAM","ROTIS","ROUG","ROVOT","RUBIT","RUMEL","SALIN",
"SALSI","SAU","SAURG","SAUX","SECHE","SIJAN","SIMAR","SOFFY","SOMOS","SOMTI",
"SONGA","SOSTO","SOSUR","SOVAR","SPEC","SU","SUBIL","TAKAT","TAN","TBO",
"TBOX","TEMPU","THUNE","TIMTA","TINOT","TIPIK","TLN","TOU","TRETS","TS",
"TUGLI","TUNEG","TURIL","UVTIN","UXANA","VAGNA","VALAG","VARES","VELIN","VEROT",
"ZEBRA","ZR"};

private TreeMap<String,Integer> indexes;

// constructor
public Waypoints_BT() {
	indexes = new TreeMap< String, Integer >();
	for	( int i = 0; i < names.length; i++ )
		indexes.put( names[i], i );
	}

// get methods
public String getName( int i ) {
	try { return names[i]; }
	catch (Exception e) { return "no_name"; }
	}

public int getIndex( String name ) {
	try { return indexes.get( name ); }
	catch (Exception e) { return -1; }
	}

/* test main function *
public static void main(String[] args) throws Exception {
	Waypoints_BT wbt = new Waypoints_BT();
	// System.out.printf( "Loaded %d waypoints\n", wbt.names.length );
	if	( args.length > 0 )
		{
		if	( args[0].matches("[0-9]+") )
			System.out.println( wbt.getName( Integer.parseInt(args[0]) ) );
		else	System.out.println( wbt.getIndex(args[0]) );
		}
	}
//*/
}
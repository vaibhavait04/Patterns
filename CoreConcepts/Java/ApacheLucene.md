# Lucene in 5 minutes

Lucene is a full-text search library in Java which makes it easy to add search functionality to an application or website.
The content you add to Lucene can be from various sources, like a SQL/NoSQL database, a filesystem, or even from websites.
To achieve fast searches, leucene creates a full-text index - allows you to perform queries, returning results ranked by either the relevance to the query or sorted by an arbitrary field such as a document's last modified date.  

Searching: Lucene is able to achieve fast search responses because, instead of searching the text directly, it searches an index instead.
This type of index is called an inverted index, because it inverts a page-centric data structure (page->words) to a keyword-centric data structure (word->pages).

An index consists of one or more Documents.  Document is the unit of search and index.
Indexing involves adding Documents to an IndexWriter, and searching involves retrieving Documents from an index via an IndexSearcher.


Example _HelloLucene_ in the repository shows the following: 
1. Create Index 
2. Query 
3. Search 
4. Display 

*** 

1. Index
For this simple case, we're going to create an in-memory index from some strings.
`
	StandardAnalyzer analyzer = new StandardAnalyzer();
	Directory index = new RAMDirectory();

	IndexWriterConfig config = new IndexWriterConfig(Version.LUCENE_40, analyzer);

	IndexWriter w = new IndexWriter(index, config);
	addDoc(w, "Lucene in Action", "193398817");
	addDoc(w, "Lucene for Dummies", "55320055Z");
	addDoc(w, "Managing Gigabytes", "55063554A");
	addDoc(w, "The Art of Computer Science", "9900333X");
	w.close();
`
addDoc() is what actually adds documents to the index:
`
	private static void addDoc(IndexWriter w, String title, String isbn) throws IOException {
	  Document doc = new Document();
	  doc.add(new TextField("title", title, Field.Store.YES));
	  doc.add(new StringField("isbn", isbn, Field.Store.YES));
	  w.addDocument(doc);
	}
`
Note the use of TextField for content we want tokenized, and StringField for id fields and the like, which we don't want tokenized.

2. Query
We read the query from stdin, parse it and build a lucene Query out of it.

	String querystr = args.length > 0 ? args[0] : "lucene";
	Query q = new QueryParser(Version.LUCENE_40, "title", analyzer).parse(querystr);
 
3. Search
Using the Query we create a Searcher to search the index. Then a TopScoreDocCollector is instantiated to collect the top 10 scoring hits.

	int hitsPerPage = 10;
	IndexReader reader = IndexReader.open(index);
	IndexSearcher searcher = new IndexSearcher(reader);
	TopScoreDocCollector collector = TopScoreDocCollector.create(hitsPerPage, true);
	searcher.search(q, collector);
	ScoreDoc[] hits = collector.topDocs().scoreDocs;
 
4. Display
Now that we have results from our search, we display the results to the user.
	System.out.println("Found " + hits.length + " hits.");
	for(int i=0;i<hits.length;++i) {
	    int docId = hits[i].doc;
	    Document d = searcher.doc(docId);
	    System.out.println((i + 1) + ". " + d.get("isbn") + "\t" + d.get("title"));
	}
 



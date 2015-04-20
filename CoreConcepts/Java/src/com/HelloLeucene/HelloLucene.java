package com.HelloLeucene;

import org.apache.lucene.store.Directory;
import org.apache.lucene.store.RAMDirectory;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;

import org.apache.lucene.document.StringField;
import org.apache.lucene.document.TextField;

import org.apache.lucene.analysis.standard.StandardAnalyzer;

import org.apache.lucene.index.DirectoryReader;

import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;

import org.apache.lucene.index.IndexWriterConfig;

import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopScoreDocCollector;

import java.io.IOException;

public class HelloLucene {
  public static void main(String[] args) throws IOException, ParseException {
    // 0. Specify the analyzer for tokenizing text.
    //    The same analyzer should be used for indexing and searching
    StandardAnalyzer analyzer = new StandardAnalyzer();

    // 1. Create the in memory index
    Directory index = new RAMDirectory();

    // use analyzer in index config
    IndexWriterConfig config = new IndexWriterConfig(analyzer);
    // Create writer to in-memory index with above config 
    IndexWriter w = new IndexWriter(index, config);
    
    addDoc(w, "Lucene in Action", "193398817");
    addDoc(w, "Lucene for Dummies", "55320055Z");
    addDoc(w, "Managing Gigabytes", "55063554A");
    addDoc(w, "The Art of Computer Science", "9900333X");
    w.close();

    // 2. Lucene query string 
    String querystr = args.length > 0 ? args[0] : "lucene";

    // "title" arg specifies default field to use when no field 
    // is explicitly specified in the query.
    Query q = new QueryParser("title", analyzer).parse(querystr);

    // 3. search - open index, search index, TopScoreDocCollect, 
    int hitsPerPage = 10;
    IndexReader reader = DirectoryReader.open(index);
    IndexSearcher searcher = new IndexSearcher(reader);
    TopScoreDocCollector collector = TopScoreDocCollector.create(hitsPerPage);
    searcher.search(q, collector);
    ScoreDoc[] hits = collector.topDocs().scoreDocs;
   
    // 4. display results
    System.out.println("Found " + hits.length + " hits.");
    for(int i=0;i<hits.length;++i) {
      int docId = hits[i].doc;
      Document d = searcher.doc(docId);
      System.out.println((i + 1) + ". " + d.get("isbn") + "\t" + d.get("title"));
    }

    // reader can only be closed when there
    // is no need to access the documents any more.
    reader.close();
  }

  private static void addDoc(IndexWriter w, String title, String isbn) throws IOException {
    Document doc = new Document();
    doc.add(new TextField("title", title, Field.Store.YES));

    // use a string field for isbn because we don't want it tokenized
    doc.add(new StringField("isbn", isbn, Field.Store.YES));
    w.addDocument(doc);
  }
}
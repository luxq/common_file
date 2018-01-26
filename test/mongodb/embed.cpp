// Last Update:2016-12-23 14:45:31
/**
 * @file embed.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-23
 */

#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

int main(int argc, const char *argv[])
{
	mongocxx::client client{mongocxx::uri{}};
	mongocxx::database db = client["newdb"];
	mongocxx::collection coll = db["test"];
	auto builder = bsoncxx::builder::stream::document();
	bsoncxx::document::value doc_value = builder
		<<"name"<<"Mongodb"
		<<"type"<<"database"
		<<"count"<<1
		<<"versions"<<bsoncxx::builder::stream::open_array
		  <<"v3.2"<<"v3.0"<<"v2.6"
		<<bsoncxx::builder::stream::close_array
		<<"info"<<bsoncxx::builder::stream::open_document
		  <<"x"<<203
		  <<"y"<<102
		<<bsoncxx::builder::stream::close_document
		<<bsoncxx::builder::stream::finalize;
	bsoncxx::document::view view = doc_value.view();
	std::string fname = "name";
	bsoncxx::document::element element = view[fname];
	if(element.type() != bsoncxx::type::k_utf8)
	{
		std::cout<<"element type error."<<std::endl;
	}
	std::string value = element.get_utf8().value.to_string();
	std::cout<<"fname = "<<fname<<",value = "<<value<<std::endl;

	/////////////mongocxx::result::insert_one result = coll.insert_one(view);
	//insert 
//	std::vector<bsoncxx::document::value> documents;
//	for(int i = 0; i < 20; i++)
//	{
//		documents.push_back(
//				bsoncxx::builder::stream::document() << "i" << i << bsoncxx::builder::stream::finalize);
//	}
//	coll.insert_many(documents);
	//query
	//1.query one.
	mongocxx::stdx::optional<bsoncxx::document::value> maybe_result = 
		coll.find_one(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);
	if(maybe_result)
	{
		std::cout<<bsoncxx::to_json(*maybe_result)<<"\n";
	}

	//2.query one that i==3
	maybe_result = 
		coll.find_one(bsoncxx::builder::stream::document{} << "i" << 3 << bsoncxx::builder::stream::finalize);
	if(maybe_result)
	{
		std::cout<<bsoncxx::to_json(*maybe_result)<<"\n";
	}

	//3.query all
	mongocxx::cursor cursor = coll.find({});
	for(auto doc : cursor)
	{
		std::cout<<bsoncxx::to_json(doc)<<"\n";
	}
	//4.query all that i>5 and i<=10
	cursor = coll.find(bsoncxx::builder::stream::document{}<<"i"<<bsoncxx::builder::stream::open_document<<
			"$gt"<<5<<
			"$lte"<<10 
			<<bsoncxx::builder::stream::close_document<<bsoncxx::builder::stream::finalize);
	for(auto doc : cursor)
	{
		std::cout<<bsoncxx::to_json(doc)<<"\n";
	}


	return 0;
}

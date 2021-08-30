/*
  1. Take functions from gen
  2. Take all objects from mappings.json
  3. Create a filename called {$Filename}.code-snippets for all objects in mappings.json
  4. Take contents from filepath and use the getSnippet function to get the string
  5. write the json data to the .code-snippets file
  
*/

import { getSnippet } from './gen';
import * as fs from 'fs';
import * as Data from './mappings.json';

const run = async () => 
{
    const {mappings} = Data;
    for(const d of mappings)
    {
        fs.readFile(d.data.filepath,"utf-8",(err,data)=>{
            let lines: string[] = data.split('\n');
            let snippetData = getSnippet(lines);
            let snippetObj = {
                scope: "cpp",
                prefix: d.data.prefix,
                body: snippetData,
                description: d.data.description
            };
            let jsonObj = {};
            jsonObj[`${d.data.name}`] = snippetObj;
            fs.writeFile(`../snippets/${d.data.name}.code-snippets`,JSON.stringify(jsonObj),(err)=>{
                if(err)
                {
                    console.error(err);
                }
                else{
                    console.log("completed successfully")
                }
            })
        });

    }
}

run();
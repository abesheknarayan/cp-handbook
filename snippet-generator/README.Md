# Snippets Generator

A simple VS-Code Snippets generator using TypeScript

## Adding Snippets Entry

Add a entry of the following object to `mappings.json` file

- __name__ : Name of the template
- __prefix__ : Prefix for the snippet 
- __filepath__ : Path where template file is located
- __description__ : Description of the template 

## Generating Snippets

Run

```Bash
npm run gen-snippets
```
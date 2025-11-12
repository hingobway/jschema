import type {} from 'npm:@types/node';
import { readFile, writeFile } from 'node:fs/promises';
import { join } from 'node:path';

import { codegen } from './quicktype.ts';

const schema = await readFile(join(__dirname, '../schema/base.json'), 'utf-8');

const code = await codegen({ name: 'base', schema, lang: 'c++', opts: {} });

await writeFile(join(__dirname, '../src/scgen.h'), code, 'utf-8');

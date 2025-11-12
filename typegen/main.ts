import type {} from 'npm:@types/node';
import { readFile, writeFile, readdir } from 'node:fs/promises';
import { dirname, fromFileUrl, join } from 'jsr:@std/path';

import { codegen } from './quicktype.ts';

const ROOT_DIR = import.meta.dirname || dirname(fromFileUrl(import.meta.url));

const schemaDir = join(ROOT_DIR, '../schema');
const entries = await readdir(schemaDir, { withFileTypes: true });
const schemas = new Map<string, string>();
for (const entry of entries) {
  if (!entry.isFile()) continue;
  const match = entry.name.match(/^(.+)\.json$/);
  if (!match) continue;
  schemas.set(match[1], await readFile(join(schemaDir, entry.name), 'utf-8'));
}

const code = await codegen({
  schemas,
  config: {
    lang: 'c++',

    rendererOptions: {
      boost: false,
      'code-format': 'with-struct',
      'include-location': 'global-include',
      namespace:'schema'
    },
  },
});

await writeFile(join(ROOT_DIR, '../src/scgen.h'), code, 'utf-8');

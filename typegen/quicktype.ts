import {
  FetchingJSONSchemaStore,
  InputData,
  JSONSchemaInput,
  quicktype,
} from 'npm:quicktype-core';

export async function codegen(opts: {
  schemas: Map<string, string>;
  config: QTOpts;
}) {
  const input = new JSONSchemaInput(new FetchingJSONSchemaStore());

  for await (const [name, schema] of opts.schemas) {
    await input.addSource({ name, schema });
  }

  const data = new InputData();
  data.addInput(input);

  const { lines } = await quicktype({
    inputData: data,
    ...opts.config,
  });
  return lines.join('\n');
}

type LangBase = Parameters<typeof quicktype>[0];
export type QTOpts = Omit<LangBase, 'inputData'>;
export type LangEnum = ExtractLiterals<LangBase['lang']>;

type ExtractLiterals<T> = T extends string
  ? string extends T
    ? never
    : T
  : never;

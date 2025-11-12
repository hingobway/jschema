import {
  FetchingJSONSchemaStore,
  InputData,
  JSONSchemaInput,
  quicktype,
  RendererOptions,
} from 'npm:quicktype-core';

export async function codegen<Lang extends LangEnum>(opts: {
  name: string;
  schema: string;
  lang: Lang;
  opts: Partial<RendererOptions<Lang>>;
}) {
  const input = new JSONSchemaInput(new FetchingJSONSchemaStore());
  await input.addSource({
    name: opts.name,
    schema: opts.schema,
  });
  const data = new InputData();
  data.addInput(input);

  const { lines } = await quicktype({
    inputData: data,
    lang: opts.lang,
    rendererOptions: opts.opts
  });
  return lines.join('\n');
}

type LangBase = Parameters<typeof quicktype>[0];
export type LangEnum = ExtractLiterals<LangBase['lang']>;

type ExtractLiterals<T> = T extends string
  ? string extends T
    ? never
    : T
  : never;

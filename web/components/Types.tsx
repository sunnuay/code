export interface APIConfig {
  listen: string;
}

export interface ForwardConfig {
  enabled: boolean;
  listen: string;
}

export interface RouteConfig {
  path: string;
  target: string;
}

export interface ReverseConfig {
  enabled: boolean;
  listen: string;
  tls: boolean;
  cert: string;
  key: string;
  routes: RouteConfig[];
}

export interface DDNSConfig {
  enabled: boolean;
  interval: number;
  api_token: string;
  domain: string;
}

export interface CertConfig {
  enabled: boolean;
  cert: string;
  key: string;
  api_token: string;
  domain: string;
}

export interface Config {
  api: APIConfig;
  forward: ForwardConfig;
  reverse: ReverseConfig;
  ddns: DDNSConfig;
  cert: CertConfig;
}

export const defaultConfig: Config = {
  api: { listen: ":10000" },
  forward: { enabled: false, listen: ":10001" },
  reverse: {
    enabled: false,
    listen: ":9999",
    tls: false,
    cert: ".cache/cert.pem",
    key: ".cache/key.pem",
    routes: [{ path: "/server/", target: "http://127.0.0.1:8080" }],
  },
  ddns: { enabled: false, interval: 600, api_token: "", domain: "" },
  cert: {
    enabled: false,
    cert: ".cache/cert.pem",
    key: ".cache/key.pem",
    api_token: "",
    domain: "",
  },
};

export const tabs = [
  { id: "forward", name: "Forward" },
  { id: "reverse", name: "Reverse" },
  { id: "ddns", name: "DDNS" },
  { id: "cert", name: "Cert" },
  { id: "settings", name: "Settings" },
] as const;

export type Theme = "latte" | "frappe" | "macchiato" | "mocha";

export interface WebConfig {
  apiUrl: string;
  theme: Theme;
}

export const defaultWebConfig: WebConfig = {
  apiUrl: "http://127.0.0.1:10000",
  theme: "latte",
};

export const themes: { id: Theme; name: string }[] = [
  { id: "latte", name: "Latte" },
  { id: "frappe", name: "Frappé" },
  { id: "macchiato", name: "Macchiato" },
  { id: "mocha", name: "Mocha" },
];

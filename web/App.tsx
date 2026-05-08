import { useState } from "react";
import {
  ShieldCheck,
  ArrowRightLeft,
  Globe,
  Lock,
  Plus,
  Square,
  RefreshCw,
  Settings,
  Server,
} from "lucide-react";

const App = () => {
  const [activeTab, setActiveTab] = useState("forward");

  const menuItems = [
    { id: "forward", name: "正向代理", icon: ShieldCheck },
    { id: "reverse", name: "反向代理", icon: ArrowRightLeft },
    { id: "ddns", name: "动态域名", icon: Globe },
    { id: "cert", name: "自动证书", icon: Lock },
  ];

  const renderForwardProxy = () => (
    <div className="space-y-6">
      <div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm">
        <div className="flex justify-between items-center mb-6">
          <h2 className="text-lg font-semibold text-gray-800">全局设置</h2>
          <span className="px-3 py-1 bg-green-100 text-green-700 text-sm rounded-full flex items-center">
            <span className="w-2 h-2 bg-green-500 rounded-full mr-2"></span>
            运行中
          </span>
        </div>

        <div className="grid grid-cols-2 gap-6">
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              监听端口
            </label>
            <input
              type="number"
              defaultValue="9999"
              className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none"
            />
          </div>
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              协议类型
            </label>
            <select className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none">
              <option>HTTP / HTTPS</option>
              <option>SOCKS5</option>
            </select>
          </div>
        </div>

        <div className="mt-6 pt-6 flex justify-end gap-4">
          <button className="flex items-center px-4 py-2 bg-gray-100 text-gray-700 hover:bg-gray-200 rounded-lg transition-colors">
            <Square size={16} className="mr-2" /> 停止服务
          </button>
          <button className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors">
            <RefreshCw size={16} className="mr-2" /> 保存并重启
          </button>
        </div>
      </div>
    </div>
  );

  const renderReverseProxy = () => (
    <div className="bg-white rounded-xl border border-gray-100 shadow-sm overflow-hidden">
      <div className="p-6 border-b border-gray-100 flex justify-between items-center">
        <h2 className="text-lg font-semibold text-gray-800">代理规则</h2>
        <button className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors">
          <Plus size={16} className="mr-2" /> 添加规则
        </button>
      </div>
      <table className="w-full text-left border-collapse">
        <thead>
          <tr className="bg-gray-50 text-gray-500 text-sm">
            <th className="px-6 py-3 font-medium">源域名</th>
            <th className="px-6 py-3 font-medium">目标地址</th>
            <th className="px-6 py-3 font-medium">状态</th>
            <th className="px-6 py-3 font-medium text-right">操作</th>
          </tr>
        </thead>
        <tbody className="divide-y divide-gray-100">
          {[
            {
              domain: "example.com",
              target: "127.0.0.1:10000",
              status: "active",
            },
            {
              domain: "api.example.com",
              target: "127.0.0.1:10001",
              status: "active",
            },
          ].map((rule, idx) => (
            <tr key={idx} className="hover:bg-gray-50">
              <td className="px-6 py-4 font-medium text-gray-800">
                {rule.domain}
              </td>
              <td className="px-6 py-4 text-gray-600">{rule.target}</td>
              <td className="px-6 py-4">
                <span className="px-2 py-1 bg-green-100 text-green-700 text-xs rounded-md">
                  生效中
                </span>
              </td>
              <td className="px-6 py-4 text-right">
                <button className="text-blue-600 hover:text-blue-800 text-sm font-medium mr-3 transition-colors">
                  编辑
                </button>
                <button className="text-red-600 hover:text-red-800 text-sm font-medium transition-colors">
                  删除
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );

  const renderDDNS = () => (
    <div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm max-w-2xl">
      <h2 className="text-lg font-semibold text-gray-800 mb-6">域名配置</h2>
      <div className="space-y-5">
        <div>
          <label className="block text-sm font-medium text-gray-700 mb-2">
            域名服务商
          </label>
          <select className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none">
            <option>Cloudflare</option>
          </select>
        </div>
        <div>
          <label className="block text-sm font-medium text-gray-700 mb-2">
            域名
          </label>
          <input
            type="text"
            placeholder="example.com"
            className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none"
          />
        </div>
        <div>
          <label className="block text-sm font-medium text-gray-700 mb-2">
            密钥
          </label>
          <input
            type="password"
            placeholder="API Token"
            className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none"
          />
        </div>

        <div className="bg-gray-50 p-4 rounded-lg border border-gray-100 flex items-center justify-between mt-6">
          <div>
            <p className="text-sm text-gray-500 mb-1">当前公网 IP</p>
            <p className="font-mono text-gray-800">2606:4700:10::ac42:93f3</p>
          </div>
          <button className="flex items-center px-4 py-2 bg-white border border-gray-200 text-gray-700 hover:bg-gray-50 rounded-lg transition-colors shadow-sm">
            <RefreshCw size={16} className="mr-2" /> 强制同步
          </button>
        </div>
      </div>
    </div>
  );

  const renderCert = () => (
    <div className="space-y-6">
      <div className="flex gap-4">
        <div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm flex-1">
          <h3 className="text-sm text-gray-500 mb-1">证书提供商</h3>
          <p className="text-lg font-medium text-gray-800 flex items-center">
            Let's Encrypt <Lock size={16} className="ml-2 text-green-500" />
          </p>
        </div>
        <div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm flex-1">
          <h3 className="text-sm text-gray-500 mb-1">通知邮箱</h3>
          <p className="text-lg font-medium text-gray-800">admin@example.com</p>
        </div>
      </div>

      <div className="bg-white rounded-xl border border-gray-100 shadow-sm overflow-hidden">
        <div className="p-6 border-b border-gray-100 flex justify-between items-center">
          <h2 className="text-lg font-semibold text-gray-800">管理列表</h2>
          <button className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors">
            <Plus size={16} className="mr-2" /> 申请新证书
          </button>
        </div>
        <table className="w-full text-left border-collapse">
          <thead>
            <tr className="bg-gray-50 text-gray-500 text-sm">
              <th className="px-6 py-3 font-medium">域名</th>
              <th className="px-6 py-3 font-medium">到期时间</th>
              <th className="px-6 py-3 font-medium">状态</th>
              <th className="px-6 py-3 font-medium text-right">操作</th>
            </tr>
          </thead>
          <tbody className="divide-y divide-gray-100">
            {[
              {
                domain: "example.com",
                expiry: "2026-01-01",
                days: 40,
                status: "valid",
              },
              {
                domain: "api.example.com",
                expiry: "2026-02-01",
                days: 9,
                status: "warning",
              },
            ].map((cert, idx) => (
              <tr key={idx} className="hover:bg-gray-50">
                <td className="px-6 py-4 font-medium text-gray-800">
                  {cert.domain}
                </td>
                <td className="px-6 py-4 text-gray-600">
                  {cert.expiry}{" "}
                  <span className="text-sm text-gray-400">
                    ({cert.days}天后)
                  </span>
                </td>
                <td className="px-6 py-4">
                  {cert.status === "valid" ? (
                    <span className="px-2 py-1 bg-green-100 text-green-700 text-xs rounded-md">
                      正常
                    </span>
                  ) : (
                    <span className="px-2 py-1 bg-yellow-100 text-yellow-700 text-xs rounded-md">
                      即将过期
                    </span>
                  )}
                </td>
                <td className="px-6 py-4 text-right">
                  <button className="text-blue-600 hover:text-blue-800 text-sm font-medium mr-3 transition-colors">
                    手动续签
                  </button>
                  <button className="text-gray-500 hover:text-gray-800 text-sm font-medium transition-colors">
                    下载
                  </button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );

  return (
    <div className="flex h-screen bg-[#F8FAFC] font-sans text-gray-900">
      <aside className="w-64 bg-white border-r border-gray-200 flex flex-col shadow-sm z-10">
        <div className="h-16 flex items-center px-6 border-b border-gray-100">
          <Server className="text-blue-600 mr-3" size={24} />
          <h1 className="text-xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-blue-600 to-indigo-600">
            web
          </h1>
        </div>

        <nav className="flex-1 py-6 px-4 space-y-1">
          {menuItems.map((item) => {
            const Icon = item.icon;
            const isActive = activeTab === item.id;
            return (
              <button
                key={item.id}
                onClick={() => setActiveTab(item.id)}
                className={`w-full flex items-center px-4 py-3 rounded-xl transition-all duration-200 ${
                  isActive
                    ? "bg-blue-50 text-blue-700 shadow-sm"
                    : "text-gray-600 hover:bg-gray-50 hover:text-gray-900"
                }`}
              >
                <Icon
                  size={20}
                  className={isActive ? "text-blue-600" : "text-gray-400"}
                />
                <span className="ml-3 font-medium">{item.name}</span>
              </button>
            );
          })}
        </nav>

        <div className="p-4 border-t border-gray-100">
          <button className="w-full flex items-center px-4 py-2 text-gray-500 hover:text-gray-800 transition-colors">
            <Settings size={20} className="mr-3" />
            <span className="font-medium">系统设置</span>
          </button>
        </div>
      </aside>

      <main className="flex-1 flex flex-col h-screen overflow-hidden">
        <header className="h-16 bg-white border-b border-gray-200 flex items-center px-8 flex-shrink-0">
          <h2 className="text-xl font-semibold text-gray-800">
            {menuItems.find((i) => i.id === activeTab)?.name}
          </h2>
        </header>

        <div className="flex-1 overflow-auto p-8">
          <div className="max-w-5xl mx-auto">
            {activeTab === "forward" && renderForwardProxy()}
            {activeTab === "reverse" && renderReverseProxy()}
            {activeTab === "ddns" && renderDDNS()}
            {activeTab === "cert" && renderCert()}
          </div>
        </div>
      </main>
    </div>
  );
};

export default App;

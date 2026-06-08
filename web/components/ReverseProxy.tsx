import { Plus } from "lucide-react";

interface Rule {
	domain: string;
	target: string;
	status: string;
}

const rules: Rule[] = [
	{ domain: "example.com", target: "127.0.0.1:10000", status: "active" },
	{ domain: "api.example.com", target: "127.0.0.1:10001", status: "active" },
];

const ReverseProxy = () => (
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
				{rules.map((rule, idx) => (
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

export default ReverseProxy;

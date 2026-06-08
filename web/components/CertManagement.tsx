import { Lock, Plus } from "lucide-react";

interface Certificate {
	domain: string;
	expiry: string;
	days: number;
	status: "valid" | "warning";
}

const certificates: Certificate[] = [
	{ domain: "example.com", expiry: "2026-01-01", days: 40, status: "valid" },
	{ domain: "api.example.com", expiry: "2026-02-01", days: 9, status: "warning" },
];

const CertManagement = () => (
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
					{certificates.map((cert, idx) => (
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

export default CertManagement;
